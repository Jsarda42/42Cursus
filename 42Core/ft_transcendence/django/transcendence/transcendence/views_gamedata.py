from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from rest_framework.permissions import IsAuthenticated
from .serializers import UserSerializer, ProfileSerializer
from django.contrib.auth import get_user_model
from django.contrib.auth.models import User
from .views import JWTAuthenticationFromCookie 
from .models import Profile, MatchHistory

from rest_framework.views import APIView
from rest_framework.parsers import MultiPartParser, FormParser
from rest_framework.response import Response
from rest_framework import status
import logging

import sys
import logging
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)
class GetWinLoss(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        profile = Profile.objects.get(user=request.user)
        data = {
            "username": request.user.username,
            "wins": profile.wins,
            "losses": profile.losses
        }
        return Response(data)

class GetMatchHistory(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]
    permission_classes = [IsAuthenticated]

    def get(self, request):
        matches = MatchHistory.objects.filter(user=request.user).order_by("-timestamp")

        history = [
            {
                "opponent": match.opponent_username,
                "user_score": match.user_score,
                "opponent_score": match.opponent_score,
                "date": match.timestamp.strftime('%Y-%m-%d %H:%M:%S')
            }
            for match in matches
        ]

        return Response({"username": request.user.username, "match_history": history})


class LeaderboardView(APIView):
    def get(self, request):
        leaderboard = Profile.objects.order_by("-wins")[:10]  # Top 10 players based on wins
        data = [
            {
                "username": profile.user.username,
                "wins": profile.wins,
                "losses": profile.losses,
                "avatar": profile.avatar.url if profile.avatar else None
            }
            for profile in leaderboard
        ]
        return Response(data)

class AddFriendView(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]
    permission_classes = [IsAuthenticated]

    def post(self, request):
        friend_username = request.data.get("friend_username")

        if not friend_username:
            return Response({"error": "Friend username is required"}, status=status.HTTP_400_BAD_REQUEST)

        try:
            friend_user = User.objects.get(username=friend_username)
            request.user.profile.add_friend(friend_user.profile)  # Add friend
            return Response({"message": f"Added {friend_username} as a friend!"})
        except User.DoesNotExist:
            return Response({"error": "User not found"}, status=status.HTTP_404_NOT_FOUND)

class FriendListView(APIView):
    authentication_classes = [JWTAuthenticationFromCookie]  # Your authentication class
    permission_classes = [IsAuthenticated]  # Ensure the user is authenticated

    def get(self, request):
        
        profile = request.user.profile
        
  
        friends = profile.friends.all()
        
        friend_data = [
            {
                "username": friend.user.username,
                "avatar": friend.avatar.url if friend.avatar else None,
                "is_online": friend.user.connect.is_online
            }
            for friend in friends
        ]
        return Response({"friends": friend_data})

