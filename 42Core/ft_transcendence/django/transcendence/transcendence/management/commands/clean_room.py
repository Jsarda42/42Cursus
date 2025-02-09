from django.core.management.base import BaseCommand
from game.models import GameRoom, GameRoomFour
import sys

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


class Command(BaseCommand):
    args=''
    help='clean rooms if the server was shutdown brutally'

    def handle(self, *args, **options):
        room = GameRoom.objects.all()
        if room == None:
            eprint("No room to clean")
        else:
            for a in room:
                a.clean()
            eprint("All room cleared")
        roomfour = GameRoomFour.objects.all()
        if roomfour == None:
            eprint("No room to clean")
        else:
            for a in roomfour:
                a.clean()
            eprint("All room cleared")