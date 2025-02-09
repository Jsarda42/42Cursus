"""
ASGI config for transcendence project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/howto/deployment/asgi/
"""

import os
from channels.auth import AuthMiddlewareStack
from transcendence.views import TokenAuthMiddleware
from channels.security.websocket import AllowedHostsOriginValidator
from channels.routing import ChannelNameRouter, ProtocolTypeRouter, URLRouter, ChannelNameRouter
from django.core.asgi import get_asgi_application
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'transcendence.settings')

django_asgi_app = get_asgi_application()

from .routing import logs_url

application = ProtocolTypeRouter({
    "http" : django_asgi_app,
    "websocket" : AllowedHostsOriginValidator(
        TokenAuthMiddleware(URLRouter(logs_url))
    ),
})
