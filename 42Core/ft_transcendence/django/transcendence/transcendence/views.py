from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from rest_framework_simplejwt.tokens import RefreshToken
from rest_framework_simplejwt.authentication import JWTAuthentication
from django.contrib.auth.models import User
from django.conf import settings
from django.urls import reverse
from rest_framework.permissions import AllowAny
from rest_framework.authentication import TokenAuthentication
from rest_framework.permissions import IsAuthenticated
from .serializers import UserSerializer, ProfileSerializer
from django.contrib.auth.hashers import check_password
from django.shortcuts import redirect
from django.http import HttpResponseRedirect
from .models import Profile, Connected


#imports for middleware jwt connection
from django.contrib.auth.models import AnonymousUser
from rest_framework.authtoken.models import Token
from channels.db import database_sync_to_async
from channels.middleware import BaseMiddleware
from transcendence.settings import SIMPLE_JWT, SECRET_KEY
import jwt
import requests
from django.core.cache import cache
import time
from .views_2FA import send_otp_email, generate_otp
import html

#imports for image management

import requests
from django.core.files.base import ContentFile
from io import BytesIO
from urllib.parse import urlparse

from rest_framework.exceptions import AuthenticationFailed
from django.utils.decorators import method_decorator
import logging
import sys
logger = logging.getLogger(__name__)
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def sanitize_input(input_string):
    return html.escape(input_string) if isinstance(input_string, str) else input_string

class SignupView(APIView):
    authentication_classes = []
    permission_classes = [AllowAny]
    def post(self, request):
        sanitized_data = {
            'email': sanitize_input(request.data.get('email', '')),
            'username': sanitize_input(request.data.get('username', '')),
            'password': request.data.get('password', ''),
            'confirm_password': request.data.get('confirm_password', ''),
        }
        serializer = UserSerializer(data=sanitized_data)
        if serializer.is_valid():
            user=serializer.save()
            profile, profile_created = Profile.objects.get_or_create(user=user)
            connection, connection_created = Connected.objects.get_or_create(user=user)
            connection.save()
            profile.save()
            return Response({"success": True, "message": "User registered successfully"}, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

class LoginView(APIView):
    authentication_classes = []
    permission_classes = [AllowAny]

    def post(self, request):
        email = request.data.get('email')
        password = request.data.get('password')

        if email and password:
            try:
                
                user = User.objects.get(email=email)
                profile = user.profile
                connection = user.connect
                if connection.is_online:
                    return Response({"error": "User is already logged in."}, status=status.HTTP_403_FORBIDDEN)

                
                if user.check_password(password):
                   
                    profile = user.profile
                    if profile.is_2fa_enabled:
                        
                        otp = generate_otp()
                        cache.set(f"otp_{user.id}", otp, timeout=300)

                        
                        send_otp_email(user.email, otp)

                      
                        return Response({
                            "success": True,
                            "need_2fa": True,
                            "message": "OTP sent to your email. Please verify to complete login.",
                            "user_id": user.id
                        }, status=status.HTTP_200_OK)
                    else:

                        user = User.objects.get(id=user.id)
                        refresh = RefreshToken.for_user(user)
                        response = Response({
                            "success": True,
                            "need_2fa": False,
                            "message": "Login successful", # "message": "Login successful without 2FA.",
                        }, status=status.HTTP_200_OK)
                        response.set_cookie('access_token', str(refresh.access_token), httponly=True, samesite='Strict')
                        response.set_cookie('refresh_token', str(refresh), httponly=True, samesite='Strict')
                        return response
                else:
                    return Response({"error": "Invalid credentials"}, status=status.HTTP_401_UNAUTHORIZED)

            except User.DoesNotExist:
                return Response({"error": "User not found"}, status=status.HTTP_404_NOT_FOUND)

        return Response({"error": "Invalid login request"}, status=status.HTTP_400_BAD_REQUEST)



    def get(self, request):
        # Handle OAuth 42 callback
        code = request.GET.get('code')
        if code:
            return self.login_with_42(code)
        return Response({"error": "Missing authorization code"}, status=status.HTTP_400_BAD_REQUEST)


    def login_with_42(self, code):
        logger.info("This is an INFO log message")
        token_url = "https://api.intra.42.fr/oauth/token"
        payload = {
            "grant_type": "authorization_code",
            "client_id": settings.OAUTH_42_CLIENT_ID,
            "client_secret": settings.OAUTH_42_CLIENT_SECRET,
            "code": code,
            "redirect_uri": settings.OAUTH_42_REDIRECT_URI,
        }
        response = requests.post(token_url, data=payload)
        if response.status_code == 200:
            token_data = response.json()
            access_token = token_data.get("access_token")

            user_info_url = "https://api.intra.42.fr/v2/me"
            headers = {"Authorization": f"Bearer {access_token}"}
            user_response = requests.get(user_info_url, headers=headers)

            if user_response.status_code == 200:
                user_data = user_response.json()
                avatar_url = user_data['image']['versions']['micro']
                logger.info(avatar_url)
                sanitized_email = sanitize_input(user_data['email'])
                sanitized_username = sanitize_input(user_data['login'])
                user, created = User.objects.get_or_create(
                    email=sanitized_email,
                    defaults={'username': sanitized_username}
                )
                if created:
                    user.set_unusable_password()
                    user.save()
               

           
                profile, profile_created = Profile.objects.get_or_create(user=user)
                connection, connection_created = Connected.objects.get_or_create(user=user)
                eprint("connection: ", connection)
                if connection.is_online:
                    return Response({"error": "User is already logged in."}, status=status.HTTP_403_FORBIDDEN)
                connection.save()
                profile.save()
                refresh = RefreshToken.for_user(user)
                response = response = HttpResponseRedirect('/')
                response.set_cookie('access_token', str(refresh.access_token), httponly=True, samesite='Strict')
                response.set_cookie('refresh_token', str(refresh), httponly=True, samesite='Strict')
                return response
            return Response({"error": "Failed to fetch user data"}, status=status.HTTP_400_BAD_REQUEST)
        return Response({"error": "Failed to fetch access token"}, status=status.HTTP_400_BAD_REQUEST)

class JWTAuthenticationFromCookie(JWTAuthentication):
    def authenticate(self, request):
        access_token = request.COOKIES.get('access_token')
        if not access_token:
            return None

        try:
            validated_token = self.get_validated_token(access_token)
        except Exception as e:
            raise AuthenticationFailed('Invalid or expired token')

        user = self.get_user(validated_token)
        return user, validated_token

class CheckAuthStatusView(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]
    permission_classes = [IsAuthenticated]
    
    def get(self, request):
        eprint("auth", request.user)
        return Response({
            'isAuthenticated': True,
            'username': request.user.username,
        })

class RefreshTokenView(APIView):
    permission_classes = [AllowAny]  

    def post(self, request):
        refresh_token = request.COOKIES.get('refresh_token')

        if not refresh_token:
            return Response({"error": "Refresh token is missing"}, status=status.HTTP_400_BAD_REQUEST)

        try:
            # Decode the refresh token
            refresh = RefreshToken(refresh_token)
            # Generate a new access token
            access_token = refresh.access_token

            response = Response({"access": str(access_token)}, status=status.HTTP_200_OK)
            response.set_cookie('access_token', str(access_token), httponly=True, samesite='Strict')
            return response

        except InvalidToken:
            return Response({"error": "Invalid refresh token"}, status=status.HTTP_401_UNAUTHORIZED)
        except Exception as e:
            return Response({"error": str(e)}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

class LogoutView(APIView):
    def post(self, request):
        response = Response({"success": True, "message": "Successfully logged out"}, status=status.HTTP_200_OK)
        response.delete_cookie('access_token')
        response.delete_cookie('refresh_token')
        return response

@database_sync_to_async
def get_user(token_key):
    try:
        user_id: int = jwt.decode(token_key, SECRET_KEY, algorithms=[SIMPLE_JWT['ALGORITHM']]).get(SIMPLE_JWT['USER_ID_CLAIM'])
    except jwt.exceptions.DecodeError:
        return AnonymousUser()
    except jwt.exceptions.ExpiredSignatureError:
        return AnonymousUser()
    try:
        return AnonymousUser() if user_id is None else User.objects.get(id=user_id)
    except User.DoesNotExist:
        return AnonymousUser()


class TokenAuthMiddleware:
    def __init__(self, app):
        self.app = app

    async def __call__(self, scope, receive, send):
        token_key = None
        try:
            dicti = dict(scope.get('headers', []))
            # eprint("does we have csrf token ? :", dicti)
            string = dicti[b'cookie'].decode('utf-8')
            list_token = string.split(';')
            for a in list_token:
                if a.find("access_token") != -1:
                    token_key=a.split('=')[1]
                    break
        except ValueError:
            token_key = None
        scope['user'] = AnonymousUser() if token_key is None else await get_user(token_key)
        # eprint("user after middleware: ", scope['user'])
        return  await self.app(scope, receive, send)


 