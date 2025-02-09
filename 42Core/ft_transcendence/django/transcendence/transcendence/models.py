from django.db import models
from django.contrib.auth.models import User

class Connected(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='connect')
    is_online = models.BooleanField(default=False)

    def __str__(self):
        return f"{self.user.username} and {self.is_online}"

class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='profile')
    bio = models.TextField(null=True, blank=True)
    avatar = models.ImageField(null=True, blank=True)
    wins = models.PositiveIntegerField(default=0)
    losses = models.PositiveIntegerField(default=0)
    room = models.BooleanField(default=False)
    friends = models.ManyToManyField("self", blank=True, symmetrical=True)
    is_2fa_enabled = models.BooleanField(default=True)

    def __str__(self):
        return self.user.username
    
    def add_friend(self, friend_profile):
        
        if friend_profile != self:  # Prevent adding self as a friend
            self.friends.add(friend_profile)
            self.save()

class MatchHistory(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name='match_history', blank=True)
    opponent_username = models.CharField(max_length=150, blank=True, default="")
    user_score = models.PositiveIntegerField(default=0,blank=True)
    opponent_score = models.PositiveIntegerField(default=0, blank=True)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.user.username} vs {self.opponent_username} on {self.timestamp.strftime('%Y-%m-%d %H:%M:%S')}"