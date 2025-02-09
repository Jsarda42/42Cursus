import json
import random
import sys
import copy
from django.contrib.auth.models import User
from transcendence.models import MatchHistory
from django.db import models
from secrets import token_hex
from channels.db import database_sync_to_async

MAX_PLAYER = 2
CENTERBALL_X = 0.5
CENTERBALL_Y = 0.5
PADDLE_WIDTH = 0.010
PADDLE_HEIGHT = 0.15
PADDLE_Y = 0.5 - PADDLE_HEIGHT / 2
RADIUS = 0.03
MOVE = 0.003
SPEED_X = 1
SPEED_Y = 0
UP = -1
DOWN = 1

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def rand_string():
    return token_hex(16)

def generate_left_connect():
    left_connect=[]
    left_connect.append({"connect" : False})
    return left_connect

def generate_right_connect():
    right_connect=[]
    right_connect.append({"connect" : False})
    return (right_connect)

def generate_game_map():
    map_objects = []
    map_objects.append({
        "type": "ball",
        "position": [CENTERBALL_X, CENTERBALL_Y],
        "speed": [SPEED_X, SPEED_Y],
        "radius": RADIUS,
        "move": MOVE,
    })
    map_objects.append({
        "type": "paddleLeft",
        "position": [0, PADDLE_Y],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move": False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleRight",
        "position": [1 - PADDLE_WIDTH, PADDLE_Y],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move" : False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "score",
        "score": [0, 0],
    })
    return map_objects
class GameRoom(models.Model):
    time = models.DateTimeField(auto_now_add=True)

    hash = models.CharField(max_length=90, blank=True, unique=True, default=rand_string)

    players = models.ManyToManyField(User, related_name="active_players", blank=True)

    LeftPlayer = models.ForeignKey(User, related_name="paddle_left", null=True, blank=True, on_delete=models.CASCADE)

    RightPlayer = models.ForeignKey(User, related_name="paddle_right", null=True, blank=True, on_delete=models.CASCADE)

    Launch = models.BooleanField(default=False)

    LeftConnect = generate_left_connect()

    RightConnect = generate_right_connect()

    map = generate_game_map()

    def join_room(self, user):
        if (self.LeftPlayer == user or self.RightPlayer == user):
            if (user == self.LeftPlayer):
                self.LeftConnect[0]["connect"] = True
                self.save()
                return (1)
            elif (user == self.RightPlayer):
                self.RightConnect[0]["connect"] = True
                self.save()
                return (2)
        else:
            self.players.add(user)
            if self.LeftPlayer is None:
                self.LeftPlayer = user
                self.LeftConnect[0]["connect"] = True
                self.save()
                return (1)
            else:
                self.RightPlayer = user
                self.RightConnect[0]["connect"] = True
                self.save()
                return (2)
        

    def is_room_full(self):
        if (self.players.count() >= MAX_PLAYER and self.LeftPlayer is not None and self.RightPlayer is not None):
            return (True)
        return (False)

    def get_map(self):
        return (self.map)

    def is_game_launch(self):
        if (self.Launch):
            return True
        return False

    def reset(self):
        self.map[0]=({
            "type": "ball",
            "position": [CENTERBALL_X, CENTERBALL_Y],
            "speed": [SPEED_X, SPEED_Y],
            "radius": RADIUS,
            "move": MOVE,
        })
        self.map[1]=({
            "type": "paddleLeft",
            "position": [0, PADDLE_Y],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move" : False,
            "move_direction": UP,
        })
        self.map[2]=({
            "type": "paddleRight",
            "position": [1 - PADDLE_WIDTH, PADDLE_Y],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move" : False,
            "move_direction": DOWN,
        })
        self.map[3]=({
            "type": "score",
            "score": [0, 0],
        })
        self.LeftConnect[0] = {"connect" : False}
        self.RightConnect[0] = {"connect" : False}

    def launched(self):
        self.Launch = True
        self.save()
    #ne pas oublier de rajouter le time

    def end_game(self, arg):
        eprint("Left")
        eprint("Right")
        MatchHistory.objects.create(user=self.LeftPlayer, opponent_username = self.RightPlayer.username,user_score = arg[0],opponent_score = arg[1])
        MatchHistory.objects.create(user=self.RightPlayer, opponent_username = self.LeftPlayer.username,user_score = arg[1],opponent_score = arg[0])
        if arg[0] == 3:
            self.LeftPlayer.profile.wins += 1
            self.RightPlayer.profile.losses += 1
            self.LeftPlayer.profile.save()
            self.RightPlayer.profile.save() 
        elif arg[1] == 3:
            self.LeftPlayer.profile.losses += 1
            self.RightPlayer.profile.wins += 1
            self.LeftPlayer.profile.save()
            self.RightPlayer.profile.save()
        self.Launch = False
        self.players.clear()
        self.LeftPlayer = None
        self.RightPlayer = None
        self.LeftConnect[0] = {"connect":False}
        self.RightConnect[0] = {"connect":False}
        self.reset()
        self.save()
        eprint("after end game", self, self.count(), self.map)

    def leftConnect(self):
        return (self.LeftConnect)
    
    def rightConnect(self):
        return (self.RightConnect)

    def disconnect(self, user):
        if user == self.LeftPlayer:
            eprint("room_disco left", self.Launch)
            self.LeftConnect[0] = {"connect":False}
            if self.Launch == False:
                eprint("room_remove left")
                self.players.remove(self.LeftPlayer)
                self.LeftPlayer = None
            self.save()
        if user == self.RightPlayer:
            eprint("room_disco right")
            self.RightConnect[0] = {"connect":False}
            if self.Launch == False:
                eprint("room_remove right")
                self.players.remove(self.RightPlayer)
                self.RightPlayer = None
            self.save()

    def clean(self):
        self.Launch = False
        self.players.clear()
        self.LeftPlayer = None
        self.RightPlayer = None
        self.reset()
        self.save()

    def count(self):
        return f"players count {self.players.count()}"
    
    def __str__(self):
        return f"{self.LeftPlayer} vs {self.RightPlayer} on {self.time.strftime('%Y-%m-%d %H:%M:%S')} and {self.LeftConnect[0]["connect"]} and {self.RightConnect[0]["connect"]}"

def get_game_room():
    eprint("GETGAMEROOM1")
    all_rooms = GameRoom.objects.all()
    eprint("GETGAMEROOM2")
    if all_rooms.count() == 0:
        room = GameRoom.objects.create()
        room.LeftPlayer = None
        room.RightPlayer = None
        eprint("GETGAMEROOM3")
    else:
        room = GameRoom.objects.all().order_by("-time").first()
        eprint("GETGAMEROOM4")
        if room.is_room_full():
            room = GameRoom.objects.create()
        elif room.players.count() == 0:
            room.clean()
    eprint("GETGAMEROOM5")
    return room

def rand_string():
    return token_hex(16)

def generate_left_connect():
    left_connect=[]
    left_connect.append({"connect" : False})
    return left_connect

def generate_right_connect():
    right_connect=[]
    right_connect.append({"connect" : False})
    return (right_connect)

SPEED_X2=0.7
SPEED_Y2=0.7
SPEED_X3=-0.7
SPEED_Y3=-0.7
PADDLE_Y2=0.25 
PADDLE_Y4=0.75
MOVE2 = 0.002

def generate_game_map_four():
    map_objects = []
    map_objects.append({
        "type": "ball",
        "position": [CENTERBALL_X, CENTERBALL_Y],
        "speed": [SPEED_X, SPEED_Y],
        "radius": RADIUS,
        "move": MOVE2,
    })
    map_objects.append({
        "type": "ball2",
        "position": [CENTERBALL_X, CENTERBALL_Y],
        "speed": [SPEED_X2, SPEED_Y2],
        "radius": RADIUS,
        "move": MOVE2,
    })
    map_objects.append({
        "type": "ball3",
        "position": [CENTERBALL_X, CENTERBALL_Y],
        "speed": [SPEED_X3, SPEED_Y3],
        "radius": RADIUS,
        "move": MOVE2,
    })
    map_objects.append({
        "type": "paddleLeft",
        "position": [0, PADDLE_Y2],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move": False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleLeft_2",
        "position": [0.25, PADDLE_Y4],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move": False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleSecondLeft",
        "position": [0, PADDLE_Y4],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move": False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleSecondLeft_2",
        "position": [0.25, PADDLE_Y2],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move": False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleRight",
        "position": [1 - PADDLE_WIDTH, PADDLE_Y2],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move" : False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleRight_2",
        "position": [1 - PADDLE_WIDTH - 0.25, PADDLE_Y4],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move" : False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleSecondRight",
        "position": [1 - PADDLE_WIDTH, PADDLE_Y4],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move" : False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "paddleSecondRight_2",
        "position": [1 - PADDLE_WIDTH - 0.25, PADDLE_Y2],
        "width": PADDLE_WIDTH,
        "height": PADDLE_HEIGHT,
        "move" : False,
        "move_direction": DOWN,
    })
    map_objects.append({
        "type": "score",
        "score": [0, 0],
    })
    return map_objects
class GameRoomFour(models.Model):
    time = models.DateTimeField(auto_now_add=True)

    hash = models.CharField(max_length=90, blank=True, unique=True, default=rand_string)

    players4 = models.ManyToManyField(User, related_name="active_player4s", blank=True)

    LeftPlayer4 = models.ForeignKey(User, related_name="paddle_left1", null=True, blank=True, on_delete=models.CASCADE)

    SecondLeftPlayer4 = models.ForeignKey(User, related_name="paddle_left2", null=True, blank=True, on_delete=models.CASCADE)

    RightPlayer4 = models.ForeignKey(User, related_name="paddle_right1", null=True, blank=True, on_delete=models.CASCADE)

    SecondRightPlayer4 = models.ForeignKey(User, related_name="paddle_right2", null=True, blank=True, on_delete=models.CASCADE)

    Launch = models.BooleanField(default=False)

    LeftConnect = generate_left_connect()

    SecondLeftConnect = generate_left_connect()

    RightConnect = generate_right_connect()

    SecondRightConnect = generate_right_connect()

    map = generate_game_map_four()

    def join_room(self, user):
        if (self.LeftPlayer4 == user or self.RightPlayer4 == user or self.SecondLeftPlayer4 == user or self.SecondRightPlayer4 == user):
            if (user == self.LeftPlayer4):
                self.LeftConnect[0]["connect"] = True
                self.save()
                return (3)
            elif (user == self.SecondLeftPlayer4):
                self.SecondLeftConnect[0]["connect"] = True
                self.save()
                return (5)
            elif (user == self.RightPlayer4):
                self.RightConnect[0]["connect"] = True
                self.save()
                return (7)
            elif (user == self.SecondRightPlayer4):
                self.SecondRightConnect[0]["connect"] = True
                self.save()
                return (9)
        else:
            self.players4.add(user)
            if self.LeftPlayer4 is None:
                self.LeftPlayer4 = user
                self.LeftConnect[0]["connect"] = True
                self.save()
                return (3)
            elif self.SecondLeftPlayer4 is None:
                self.SecondLeftPlayer4 = user
                self.SecondLeftConnect[0]["connect"] = True
                self.save()
                return (5)
            elif self.RightPlayer4 is None:
                self.RightPlayer4 = user
                self.RightConnect[0]["connect"] = True
                self.save()
                return (7)
            else:
                self.SecondRightPlayer4 = user
                self.SecondRightConnect[0]["connect"] = True
                self.save()
                return (9)
            
        

    def is_room_full(self):
        if (self.players4.count() >= 4 and self.LeftPlayer4 is not None and self.RightPlayer4 is not None and self.SecondLeftPlayer4 is not None and self.SecondRightPlayer4 is not None):
            return (True)
        return (False)

    def get_map(self):
        return (self.map)

    def is_game_launch(self):
        if (self.Launch):
            return True
        return False

    def reset(self):
        self.map[0] = ({
            "type": "ball",
            "position": [CENTERBALL_X, CENTERBALL_Y],
            "speed": [SPEED_X, SPEED_Y],
            "radius": RADIUS,
            "move": MOVE,
        })
        self.map[1] = ({
            "type": "ball2",
            "position": [CENTERBALL_X, CENTERBALL_Y],
            "speed": [SPEED_X2, SPEED_Y2],
            "radius": RADIUS,
            "move": MOVE,
        })
        self.map[2] = ({
            "type": "ball3",
            "position": [CENTERBALL_X, CENTERBALL_Y],
            "speed": [SPEED_X3, SPEED_Y3],
            "radius": RADIUS,
            "move": MOVE,
        })
        self.map[3] = ({
            "type": "paddleLeft",
            "position": [0, PADDLE_Y2],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move": False,
            "move_direction": DOWN,
        })
        self.map[4] = ({
            "type": "paddleLeft_2",
            "position": [0.25, PADDLE_Y4],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move": False,
            "move_direction": DOWN,
        })
        self.map[5] = ({
            "type": "paddleSecondLeft",
            "position": [0, PADDLE_Y4],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move": False,
            "move_direction": DOWN,
        })
        self.map[6] = ({
            "type": "paddleSecondLeft_2",
            "position": [0.25, PADDLE_Y2],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move": False,
            "move_direction": DOWN,
        })
        self.map[7] = ({
            "type": "paddleRight",
            "position": [1 - PADDLE_WIDTH, PADDLE_Y2],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move" : False,
            "move_direction": DOWN,
        })
        self.map[8] = ({
            "type": "paddleRight_2",
            "position": [1 - PADDLE_WIDTH - 0.25, PADDLE_Y4],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move" : False,
            "move_direction": DOWN,
        })
        self.map[9] = ({
            "type": "paddleSecondRight",
            "position": [1 - PADDLE_WIDTH, PADDLE_Y4],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move" : False,
            "move_direction": DOWN,
        })
        self.map[10] = ({
            "type": "paddleSecondRight_2",
            "position": [1 - PADDLE_WIDTH - 0.25, PADDLE_Y2],
            "width": PADDLE_WIDTH,
            "height": PADDLE_HEIGHT,
            "move" : False,
            "move_direction": DOWN,
        })
        self.map[11]=({
            "type": "score",
            "score": [0, 0],
        })
        self.LeftConnect[0] = {"connect" : False}
        self.SecondLeftConnect[0] = {"connect" : False}
        self.SecondRightConnect[0] = {"connect" : False}
        self.RightConnect[0] = {"connect" : False}

    def launched(self):
        self.Launch = True
        self.save()
    #ne pas oublier de rajouter le time

    def end_game(self, arg):
        eprint("Left")
        eprint("Right")
        MatchHistory.objects.create(user=self.LeftPlayer4, opponent_username =f"{self.RightPlayer4.username} and {self.SecondRightPlayer4}" ,user_score = arg[0],opponent_score = arg[1])
        MatchHistory.objects.create(user=self.SecondLeftPlayer4, opponent_username = f"{self.RightPlayer4.username} and {self.SecondRightPlayer4}" ,user_score = arg[0],opponent_score = arg[1])
        MatchHistory.objects.create(user=self.RightPlayer4, opponent_username = f"{self.LeftPlayer4.username} and {self.SecondLeftPlayer4}" ,user_score = arg[1],opponent_score = arg[0])
        MatchHistory.objects.create(user=self.SecondRightPlayer4, opponent_username = f"{self.LeftPlayer4.username} and {self.SecondLeftPlayer4}",user_score = arg[1],opponent_score = arg[0])
        if arg[0] == 2:
            self.LeftPlayer4.profile.wins += 1
            self.RightPlayer4.profile.losses += 1
            self.SecondLeftPlayer4.profile.wins += 1
            self.SecondRightPlayer4.profile.losses += 1
            self.SecondLeftPlayer4.profile.save()
            self.SecondRightPlayer4.profile.save() 
            self.LeftPlayer4.profile.save()
            self.RightPlayer4.profile.save() 
        elif arg[1] == 2:
            self.LeftPlayer4.profile.losses += 1
            self.RightPlayer4.profile.wins += 1
            self.SecondLeftPlayer4.profile.losses += 1
            self.SecondRightPlayer4.profile.wins += 1
            self.SecondLeftPlayer4.profile.save()
            self.SecondRightPlayer4.profile.save() 
            self.LeftPlayer4.profile.save()
            self.RightPlayer4.profile.save()
        self.Launch = False
        self.players4.clear()
        self.LeftPlayer4 = None
        self.RightPlayer4 = None
        self.SecondLeftPlayer4 = None
        self.SecondRightPlayer4 = None
        self.LeftConnect[0] = {"connect":False}
        self.SecondLeftConnect[0] = {"connect":False}
        self.SecondRightConnect[0] = {"connect":False}
        self.RightConnect[0] = {"connect":False}
        self.reset()
        self.save()
        eprint("after end game", self, self.count(), self.map)

    def leftConnect(self):
        return (self.LeftConnect)
    
    def rightConnect(self):
        return (self.RightConnect)

    def disconnect(self, user):
        if user == self.LeftPlayer4:
            eprint("room_disco left4", self.Launch)
            self.LeftConnect[0] = {"connect":False}
            if self.Launch == False:
                eprint("room_remove left")
                self.players4.remove(self.LeftPlayer4)
                self.LeftPlayer4 = None
            self.save()
        elif user == self.SecondLeftPlayer4:
            eprint("room_disco secondleft", self.Launch)
            self.SecondLeftConnect[0] = {"connect":False}
            if self.Launch == False:
                eprint("room_remove secondleft")
                self.players4.remove(self.SecondLeftPlayer4)
                self.SecondLeftPlayer4 = None
            self.save()
        elif user == self.RightPlayer4:
            eprint("room_disco right")
            self.RightConnect[0] = {"connect":False}
            if self.Launch == False:
                eprint("room_remove right")
                self.players4.remove(self.RightPlayer4)
                self.RightPlayer4 = None
            self.save()
        elif user == self.SecondRightPlayer4:
            eprint("room_disco secondright", self.Launch)
            self.SecondRightConnect[0] = {"connect":False}
            if self.Launch == False:
                eprint("room_remove left")
                self.players4.remove(self.SecondRightPlayer4)
                self.SecondRightPlayer4 = None
            self.save()
        eprint(self)

    def clean(self):
        self.Launch = False
        self.players4.clear()
        self.LeftPlayer4 = None
        self.RightPlayer4 = None
        self.SecondLeftPlayer4 = None
        self.SecondRightPlayer4 = None
        self.reset()
        self.save()

    def count(self):
        return f"players4 count {self.players4.count()}"
    
    def __str__(self):
        return f"{self.LeftPlayer4} and {self.SecondLeftPlayer4} vs {self.RightPlayer4} and {self.SecondRightPlayer4} on {self.time.strftime('%Y-%m-%d %H:%M:%S')} and {self.LeftConnect[0]["connect"]} and {self.RightConnect[0]["connect"]}"

def get_game_room_four():
    eprint("GETGAMEROOM1")
    all_rooms = GameRoomFour.objects.all()
    eprint("GETGAMEROOM2")
    if all_rooms.count() == 0:
        room = GameRoomFour.objects.create()
        room.LeftPlayer4 = None
        room.RightPlayer4 = None
        eprint("GETGAMEROOM3")
    else:
        room = GameRoomFour.objects.all().order_by("-time").first()
        eprint("GETGAMEROOM4")
        if room.is_room_full():
            eprint("CREATEGETGAMEROOM")
            room = GameRoomFour.objects.create()
        elif room.players4.count() == 0:
            room.clean()
    eprint("GETGAMEROOM5")
    return room