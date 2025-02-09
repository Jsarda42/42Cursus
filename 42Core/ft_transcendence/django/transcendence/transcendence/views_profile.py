from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from rest_framework.permissions import IsAuthenticated
from .serializers import UserSerializer, ProfileSerializer
from django.contrib.auth import get_user_model
from .views import JWTAuthenticationFromCookie 
from PIL import Image, UnidentifiedImageError

from rest_framework.views import APIView
from rest_framework.parsers import MultiPartParser, FormParser
from rest_framework.response import Response
from rest_framework import status
import logging
from channels.db import database_sync_to_async
import sys
import logging
import html

logger = logging.getLogger(__name__)

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def sanitize_input(input_string):
    return html.escape(input_string) if isinstance(input_string, str) else input_string

class UserProfileView(APIView):

    authentication_classes = [JWTAuthenticationFromCookie]
    permission_classes = [IsAuthenticated]

    def get(self, request, format=None):
        """
        Retrieve the current user's profile, including user info and profile.
        """
        user = request.user
        eprint(user)
        user_serializer = UserSerializer(user)
        profile_serializer = ProfileSerializer(user.profile)  # Accessing the profile related to the user
        return Response({
            'user': user_serializer.data,
            'profile': profile_serializer.data
        })

class AvatarUploadView(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]
    permission_classes = [IsAuthenticated]
    parser_classes = [MultiPartParser, FormParser]  # To handle file uploads

    def put(self, request, format=None):
        """
        Handle avatar uploads for the authenticated user.
        """
        user = request.user
        logger.debug("Avatar upload request received for user: %s", user)

        # Check if avatar is included in the request
        avatar_file = request.FILES.get('avatar')
        if not avatar_file:
            logger.error("No avatar file provided in the request.")
            return Response({"error": "No avatar file provided."}, status=status.HTTP_400_BAD_REQUEST)

        # Validate the file using Pillow
        try:
            # Open the uploaded file with Pillow
            image = Image.open(avatar_file)

            image.verify() 
            # Ensure the image is in an acceptable format
            valid_formats = ['JPEG', 'PNG']  # Add or modify as needed
            if image.format not in valid_formats:
                logger.error("Invalid image format: %s", image.format)
                return Response(
                    {"error": f"Invalid image format. Supported formats: {', '.join(valid_formats)}"},
                    status=status.HTTP_400_BAD_REQUEST
                )

            # Check file size (e.g., max 5MB)
            max_size = 5 * 1024 * 1024  # 5 MB
            if avatar_file.size > max_size:
                logger.error("Avatar file size exceedlogger = logging.getLogger(__name__)s the limit: %d bytes", avatar_file.size)
                return Response({"error": "Avatar file size must not exceed 5MB."}, status=status.HTTP_400_BAD_REQUEST)

            # Check image dimensions (optional)
            max_width, max_height = 1024, 1024  # Example limits
            if image.width > max_width or image.height > max_height:
                logger.error("Avatar dimensions too large: %dx%d", image.width, image.height)
                return Response(
                    {"error": f"Avatar dimensions must not exceed {max_width}x{max_height} pixels."},
                    status=status.HTTP_400_BAD_REQUEST
                )

        except UnidentifiedImageError:
            logger.error("Uploaded file is not a valid image.")
            return Response({"error": "Uploaded file is not a valid image."}, status=status.HTTP_400_BAD_REQUEST)
        except Exception as e:
            logger.error("An error occurred while validating the image: %s", str(e))
            return Response({"error": "An error occurred while processing the image."}, status=status.HTTP_400_BAD_REQUEST)

        # Save the avatar
        profile = user.profile  # Assuming the user has a related profile
        profile.avatar = avatar_file  # Assign the uploaded file to the avatar field
        profile.save()  # Save the profile instance with the new avatar

        avatar_url = profile.avatar.url

        logger.debug("Avatar uploaded successfully for user: %s", user)
        return Response({
            "message": "Avatar uploaded successfully.",
            "avatar_url": avatar_url
        }, status=status.HTTP_200_OK)


class UsernameUpdateView(APIView):
    authentication_classes = [JWTAuthenticationFromCookie] 
    permission_classes = [IsAuthenticated] 

    def post(self, request, format=None):
        """
        Modify the authenticated user's username.
        """
        user = request.user
        new_username = request.data.get("username")
        sanitized_username = sanitize_input(new_username)
        request.data["username"] = sanitized_username

        serializer = UserSerializer(user, data=request.data, partial=True)

     
        if serializer.is_valid():
            serializer.save()
            return Response({
                "message": "Username updated successfully.",
                "user": serializer.data
            }, status=status.HTTP_200_OK)


        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class Modify2FAView(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]  # Assuming JWT is being used for authentication
    permission_classes = [IsAuthenticated]

    def get(self, request, format=None):
        """
        Retrieve the current 2FA status for the authenticated user.
        """
        user = request.user
        profile = user.profile  # Access the user's profile

        # Return the current 2FA status
        return Response({
            "is_2fa_enabled": profile.is_2fa_enabled
        }, status=status.HTTP_200_OK)

    def post(self, request, format=None):
        """
        Enable or disable 2FA for the authenticated user.
        """
        user = request.user
        profile = user.profile  # Access the user's profile

        # Check if the request contains a valid 'is_2fa_enabled' value
        is_2fa_enabled = request.data.get('is_2fa_enabled', None)
        
        if is_2fa_enabled is None:
            return Response({"error": "'is_2fa_enabled' field is required."}, status=status.HTTP_400_BAD_REQUEST)

        # Validate if the provided value is a boolean
        if not isinstance(is_2fa_enabled, bool):
            return Response({"error": "'is_2fa_enabled' must be a boolean value."}, status=status.HTTP_400_BAD_REQUEST)

        # Update the 2FA setting in the profile
        profile.is_2fa_enabled = is_2fa_enabled
        profile.save()

        # Return success response
        return Response({
            "message": "2FA setting updated successfully.",
            "is_2fa_enabled": profile.is_2fa_enabled
        }, status=status.HTTP_200_OK)
