from django.urls import re_path

from . import consumers
from game.consumers import GameConsumer, GameConsumerFour

logs_url = [
    re_path(r"ws/logs/", consumers.LogsConsumer.as_asgi()),
    re_path(r"ws/game/", GameConsumer.as_asgi()),
    re_path(r"ws/game_four/", GameConsumerFour.as_asgi()),
]