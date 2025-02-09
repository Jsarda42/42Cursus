"""
URL configuration for transcendence project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.1/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path, re_path, include
from django.views.generic import TemplateView
from . import auth_app
from .import view_logout
from rest_framework_simplejwt.views import TokenRefreshView
from .views import SignupView, LoginView, CheckAuthStatusView, RefreshTokenView, LogoutView
from .views_profile import UserProfileView, AvatarUploadView, UsernameUpdateView, Modify2FAView
from .views_2FA import VerifyOTPView
from .views_gamedata import GetWinLoss, GetMatchHistory, LeaderboardView, AddFriendView, FriendListView
from django.conf import settings
from django.conf.urls.static import static


urlpatterns = [
    *static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT),
	path('', TemplateView.as_view(template_name="index.html"), name='home'),

	path('api/signup/', SignupView.as_view(), name='signup'),
	path('api/login/', LoginView.as_view(), name='signin'),
	path('logout/', LogoutView.as_view(), name='logout'),
    path('api/2fa/', VerifyOTPView.as_view(), name='2fa'),	

    #Handle JWT tokens URL
    path('api/check-auth/', CheckAuthStatusView.as_view(), name='check_auth_status'),
    path('api/refresh-token/', RefreshTokenView.as_view(), name='refresh_token'),

    #User settings URL
    path('api/user-profile/', UserProfileView.as_view(), name='user_profile'),
    path('api/avatar/', AvatarUploadView.as_view(), name='avatar-upload'),
    path('api/username/', UsernameUpdateView.as_view(), name='username-upload'),
    path('api/change_2fa/', Modify2FAView.as_view(), name='modify_2fa'),


    #Match history and w/l info

    path('api/wl/', GetWinLoss.as_view(), name='wl_info'),
    path('api/matchhistory/', GetMatchHistory.as_view(), name='match_history'),
    path('api/leaderboard/', LeaderboardView.as_view(), name='leaderboard'),

    #Friends
    
    path('api/add_friend/', AddFriendView.as_view(), name='add_friend'),
    path('api/friends/', FriendListView.as_view(), name='friend-list'),


    path('auth/42/start/', auth_app.redirect_to_42, name='start_oauth'),
    path('auth/42/callback/', LoginView.as_view(), name='callback_42'),

	re_path(r'^(?!auth/42/callback|api/).*$', TemplateView.as_view(template_name="index.html"), name='index'),
]


if settings.DEBUG:
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)