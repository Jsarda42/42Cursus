#imports for 2FA

import random
from django.core.mail import send_mail
from django.conf import settings
from rest_framework.response import Response
from rest_framework import status
from rest_framework.permissions import AllowAny
from rest_framework.views import APIView
from django.core.cache import cache
from .serializers import UserSerializer
from django.contrib.auth.models import User
from rest_framework_simplejwt.tokens import RefreshToken
from rest_framework_simplejwt.authentication import JWTAuthentication
import time
import secrets

def generate_otp():
    return secrets.randbelow(10**6)

def send_otp_email(email, otp):
    """Send an OTP to the user's email address."""
    subject = "Your Two-Factor Authentication Code"
    message = f"Your OTP is: {otp}. It will expire in 5 minutes."
    from_email = settings.EMAIL_HOST_USER
    recipient_list = [email]

    send_mail(subject, message, from_email, recipient_list)

class VerifyOTPView(APIView):
    authentication_classes = []
    permission_classes = [AllowAny]

    def post(self, request):
        user_id = request.data.get('user_id')
        otp = request.data.get('otp')

        if not user_id or not otp:
            return Response({"error": "User ID and OTP are required."}, status=status.HTTP_400_BAD_REQUEST)

        # Retrieve OTP from cache
        cached_otp = cache.get(f"otp_{user_id}")
        if cached_otp and str(cached_otp) == str(otp):
            # OTP is valid, complete login
            try:
                user = User.objects.get(id=user_id)
                refresh = RefreshToken.for_user(user)
                response = Response({
                    "success": True,
                    "message": "Login successful",
                }, status=status.HTTP_200_OK)
                response.set_cookie('access_token', str(refresh.access_token), httponly=True, samesite='Strict')
                response.set_cookie('refresh_token', str(refresh), httponly=True, samesite='Strict')

                # Clear OTP from cache
                cache.delete(f"otp_{user_id}")
                return response
            except User.DoesNotExist:
                return Response({"error": "User not found"}, status=status.HTTP_404_NOT_FOUND)

        return Response({"error": "Invalid or expired OTP."}, status=status.HTTP_400_BAD_REQUEST)
