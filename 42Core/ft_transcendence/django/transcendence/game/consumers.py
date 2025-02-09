from channels.generic.websocket import AsyncWebsocketConsumer
from transcendence.models import  Profile
import json
import sys
import copy
import math
import asyncio
from game.models import GameRoom, get_game_room
from channels.db import database_sync_to_async
from asgiref.sync import sync_to_async
from game.models import CENTERBALL_X, CENTERBALL_Y, SPEED_X, SPEED_Y, RADIUS, MOVE, MOVE2, DOWN, UP, PADDLE_HEIGHT
def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


PADDLE_SPEED = 0.01
MAX_SPEED = 0.05
class GameConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        if self.scope["user"].is_anonymous:
            self.user = None
            eprint("Failed caused anonymous")
            await self.close()
        else:
            eprint("Conencted!")
            eprint("Username:", self.scope["user"])
            self.user = self.scope["user"]
            eprint("trying")
            self.room = await GameRoom.objects.filter(players=self.user).afirst()
            eprint("found", await sync_to_async(self.room.__str__)())
            if self.room != None:
                self.side = await sync_to_async(self.room.join_room)(self.user)
                self.map = await sync_to_async(self.room.get_map)()
                self.LeftConnect = self.room.LeftConnect
                self.RightConnect = self.room.RightConnect
                eprint("LeftConnect",self.room.LeftConnect[0]["connect"])
                eprint("RightConnect",self.room.RightConnect[0]["connect"])
                await self.channel_layer.group_add(self.room.hash, self.channel_name)
                await self.accept()
                await self.channel_layer.group_send(self.room.hash, {
                    'type': 'user.joined',
                    'data':{
                        'username': self.user.username
                    }
                })
                await self.send(text_data=json.dumps({
                    'event':'game_start',
                    'user': self.user.username,
                }))
            else :
                self.room = await sync_to_async(get_game_room)()
                self.side = await sync_to_async(self.room.join_room)(self.user)
                eprint("TEST1" , await sync_to_async(self.room.__str__)())
                self.map = await sync_to_async(self.room.get_map)()
                self.LeftConnect = self.room.LeftConnect
                self.RightConnect = self.room.RightConnect
                eprint("LeftConnect", self.room.LeftConnect[0]["connect"])
                eprint("RightConnect", self.room.RightConnect[0]["connect"])
                test = await  GameRoom.objects.filter(players=self.user).afirst()
                eprint("TEST2", await sync_to_async(test.__str__)())
                eprint(self.map)
                eprint("GROUP: ", self.room.hash)
                eprint("TEST3", self.room)
                await self.channel_layer.group_add(self.room.hash, self.channel_name)
                eprint("TEST5")
                await self.accept()
                eprint("TEST6")
                await self.channel_layer.group_send(self.room.hash, {
                    'type': 'user.joined',
                    'data':{
                        'username': self.user.username
                    }
                })
                eprint("TEST7")
                is_full = await sync_to_async(self.room.is_room_full)()
                eprint(is_full)
                launch = await sync_to_async(self.room.is_game_launch)()
                eprint("TEST9")
                if is_full:
                    eprint("ROOM FULL")
                    await sync_to_async(self.room.launched)()
                    await self.channel_layer.group_send(self.room.hash, {
                        'type': 'room.full',
                        'left_player': self.room.LeftPlayer.username,
                        'right_player': self.room.RightPlayer.username,
                        'data': {}
                    })
                    asyncio.create_task(self.game_loop())

    async def receive(self, text_data):
        obj = json.loads(text_data)
        eprint("receive", obj)
        if (obj["message"] == "stop"):
            await self.close()
        else :
            if obj["message"] == 'down' and self.map[self.side]["position"][1] < 1:
                eprint(self.map[self.side]["move"], " hmm ", not self.map[self.side]["move"], "hmm ", self.side)
                self.map[self.side]["move"] = not self.map[self.side]["move"]
                self.map[self.side]["move_direction"] = DOWN
            elif obj["message"] == 'up' and self.map[self.side]["position"][1] > 0:
                eprint(self.map[self.side]["move"], " hmm ", not self.map[self.side]["move"], "hmm ", self.side )
                self.map[self.side]["move"] = not self.map[self.side]["move"]
                self.map[self.side]["move_direction"] = UP
            else:
                self.map[self.side]["move"] = False
    
    async def disconnect(self, code):
        eprint("disconnect:", self.user)
        if self.room != None:
            eprint("in room:", self.user)
            await self.room.disconnect(self.user)
            eprint(await sync_to_async(self.room.count)())
            await self.channel_layer.group_discard(
                self.room.hash, self.channel_name
            )

    
    async def paddle_move(self, event):
        if event["move"] == 'down' and self.map[event["player"]]["position"][1] < 1:
            eprint(self.map[event["player"]]["move"], " hmm ", not self.map[event["player"]]["move"])
            self.map[event["player"]]["move"] = not self.map[event["player"]]["move"]
            self.map[event["player"]]["move_direction"] = DOWN
        elif self.map[event["player"]]["position"][1] > 0:
            eprint(self.map[event["player"]]["move"], " hmm ", not self.map[event["player"]]["move"])
            self.map[event["player"]]["move"] = not self.map[event["player"]]["move"]
            self.map[event["player"]]["move_direction"] = UP 

    async def user_joined(self, event):
        # eprint("MSG")
        await self.send(text_data=json.dumps({
            'event':'user_joined',
            'user': self.user.username,
            **event['data']
        }))

    async def room_full(self, event):
        self.room.Launch = True
        await self.send(text_data=json.dumps({
            'event':'game_wait',
            'user': self.user.username,
            'left_player' : event['left_player'],
            'right_player' : event['right_player'],
            **event['data'],
        }))
        
    async def game_loop(self):
        await asyncio.sleep(3)
        await self.channel_layer.group_send(self.room.hash, {
            'type' : 'game.start',
        })
        while self.map[3]["score"][0] < 3 and self.map[3]["score"][1] < 3 and (self.room.LeftConnect[0]["connect"] or self.room.RightConnect[0]["connect"]):
            state = self.get_game_state()
            await self.channel_layer.group_send(self.room.hash, {
                'type':'game.state',
                'state' : state,
                'user' : self.user.username
            })
            await asyncio.sleep(0.016)
        await self.channel_layer.group_discard(self.room.hash, self.channel_name)
        await self.channel_layer.group_send(self.room.hash, {
            'type' : 'game.end',
        })
        ending = self.room
        self.room = None
        await sync_to_async(ending.end_game)(self.map[3]["score"])
        await sync_to_async(ending.reset)()
        eprint(ending.map)
        
    async def game_start(self, event):
        await self.send(text_data=json.dumps({
            'event' : 'game_start',
            'user': self.user.username,
        }))

    async def game_end(self, event):
        eprint("GAME END")
        await self.channel_layer.group_discard(
            self.room.hash, self.channel_name
        )
        self.room = None
        await self.send(text_data=json.dumps({
            'event' : 'game_end',
            'user': self.user.username,
        }))
        self.disconnect(0)
    
    def get_game_state(self):
        ball = self.map[0]
        paddleleft = self.map[1]
        paddleright = self.map[2]
        score = self.map[3]
        if ball["position"][1] + ball["radius"] / 2 + ball["speed"][1] * ball["move"] > 1 or ball["position"][1] + ball["speed"][1] * ball["move"] < 0:
            ball["speed"][1] = -ball["speed"][1]
        if ball["position"][0] + ball["speed"][0] * ball["move"]> paddleright["position"][0] and ball["position"][1] > paddleright["position"][1] and ball["position"][1] < paddleright["position"][1] + paddleright["height"]:
            ball = self.check_collision_right()
        if ball["position"][0] + ball["speed"][0] * ball["move"] < paddleleft["position"][0] + paddleleft["width"] and ball["position"][1] > paddleleft["position"][1] and ball["position"][1] < paddleleft["position"][1] + paddleleft["height"]:
            ball = self.check_collision_left()
        ball["position"][0] += ball["speed"][0] * ball["move"]
        ball["position"][1] += ball["speed"][1] * ball["move"]
        if paddleleft["move"]: 
            if paddleleft["move_direction"] > 0 and paddleleft["position"][1] < 1 - PADDLE_HEIGHT:
                paddleleft["position"][1] += PADDLE_SPEED * paddleleft["move_direction"]
            elif paddleleft["move_direction"] < 0 and paddleleft["position"][1] > 0:
                paddleleft["position"][1] += PADDLE_SPEED * paddleleft["move_direction"]
        if paddleright["move"]: 
            if paddleright["move_direction"] > 0 and paddleright["position"][1] < 1 - PADDLE_HEIGHT:
                paddleright["position"][1] += PADDLE_SPEED * paddleright["move_direction"]
            elif paddleright["move_direction"] < 0 and paddleright["position"][1] > 0:
                paddleright["position"][1] += PADDLE_SPEED * paddleright["move_direction"]
        if ball["position"][0] > 1 - paddleright["width"] / 2 :
            ball = ({
                "type": "ball",
                "position": [CENTERBALL_X, CENTERBALL_Y],
                "speed": [SPEED_X, SPEED_Y],
                "radius": RADIUS,
                "move": MOVE,
            })
            score["score"][0] = score["score"][0] + 1
        if ball["position"][0] < 0 + paddleleft["width"] / 2 :
            ball = ({
                "type": "ball",
                "position": [CENTERBALL_X, CENTERBALL_Y],
                "speed": [-SPEED_X, SPEED_Y],
                "radius": RADIUS,
                "move": MOVE,
            })
            score["score"][1] = score["score"][1] + 1
        self.map[0] = ball
        return (json.dumps(self.map))

    def check_collision_right(self):
        ball = self.map[0]
        paddleright = self.map[2]
        relativeImpact = (ball["position"][1] - (paddleright["position"][1] + paddleright["height"] / 2)) / (paddleright["height"] / 2)
        maxAngle = math.pi / 4
        angle = relativeImpact * maxAngle
        ball["speed"][1] = math.sin(angle)
        ball["speed"][0] = -math.cos(angle)
        eprint("After collision Right: ",  ball["speed"])
        if ball["move"] < MAX_SPEED:
            ball["move"] = ball["move"] * 1.1
            eprint("ball speed: ", ball["move"])
        return ball

    def check_collision_left(self):
        ball = self.map[0]
        paddleLeft = self.map[1]
        relativeImpact = (ball["position"][1] - (paddleLeft["position"][1] + paddleLeft["height"] / 2)) / (paddleLeft["height"] / 2)
        maxAngle = math.pi / 4
        angle = relativeImpact * maxAngle
        ball["speed"][1] = math.sin(angle)
        ball["speed"][0] = math.cos(angle)
        eprint("After collision Left:",  angle, ball["speed"])
        if ball["move"] < MAX_SPEED:
            ball["move"] = ball["move"] * 1.1
            eprint("ball speed: ", ball["move"])
        return ball

    async def game_state(self, event):
        message = event["state"]
        await self.send(text_data=json.dumps({
            'type':'game_state',
            'message': message,
            'user': self.user.username,
        }))
###################################################################################################
 ##################################################################################################   
###################################################################################################
 ##################################################################################################
###################################################################################################
 ##################################################################################################
###################################################################################################
 ##################################################################################################
from game.models import GameRoomFour, get_game_room_four
class GameConsumerFour(AsyncWebsocketConsumer):

    async def connect(self):
        if self.scope["user"].is_anonymous:
            self.user = None
            eprint("Failed caused anonymous")
            await self.close()
        else:
            eprint("Conencted!")
            eprint("Username:", self.scope["user"])
            self.user = self.scope["user"]
            eprint("trying")
            self.room = await GameRoomFour.objects.filter(players4=self.user).afirst()
            eprint("found", await sync_to_async(self.room.__str__)())
            if self.room != None:
                self.side = await sync_to_async(self.room.join_room)(self.user)
                self.map = await sync_to_async(self.room.get_map)()
                self.LeftConnect = self.room.LeftConnect
                self.SecondLeftConnect = self.room.SecondLeftConnect
                self.RightConnect = self.room.RightConnect
                self.SecondRightConnect = self.room.SecondRightConnect
                eprint("SecondLeftConnect",self.room.SecondLeftConnect[0]["connect"])
                eprint("SecondRightConnect",self.room.SecondRightConnect[0]["connect"])
                eprint("LeftConnect",self.room.LeftConnect[0]["connect"])
                eprint("RightConnect",self.room.RightConnect[0]["connect"])
                await self.channel_layer.group_add(self.room.hash, self.channel_name)
                await self.accept()
                await self.channel_layer.group_send(self.room.hash, {
                    'type': 'user.joined',
                    'data':{
                        'username': self.user.username
                    }
                })
                await self.send(text_data=json.dumps({
                    'event':'game_start',
                    'user': self.user.username,
                }))
            else :
                self.room = await sync_to_async(get_game_room_four)()
                self.side = await sync_to_async(self.room.join_room)(self.user)
                eprint("TEST1" , await sync_to_async(self.room.__str__)())
                self.map = await sync_to_async(self.room.get_map)()
                self.LeftConnect = self.room.LeftConnect
                self.SecondLeftConnect = self.room.SecondLeftConnect
                self.RightConnect = self.room.RightConnect
                self.SecondRightConnect = self.room.SecondRightConnect
                eprint("SecondLeftConnect",self.room.SecondLeftConnect[0]["connect"])
                eprint("SecondRightConnect",self.room.SecondRightConnect[0]["connect"])
                eprint("LeftConnect", self.room.LeftConnect[0]["connect"])
                eprint("RightConnect", self.room.RightConnect[0]["connect"])
                test = await  GameRoomFour.objects.filter(players4=self.user).afirst()
                eprint("TEST2", await sync_to_async(test.__str__)())
                eprint(self.map)
                eprint("GROUP: ", self.room.hash)
                eprint("TEST3", self.room)
                await self.channel_layer.group_add(self.room.hash, self.channel_name)
                # eprint("TEST5")
                await self.accept()
                # eprint("TEST6")
                await self.channel_layer.group_send(self.room.hash, {
                    'type': 'user.joined',
                    'data':{
                        'username': self.user.username
                    }
                })
                # eprint("TEST7")
                is_full = await sync_to_async(self.room.is_room_full)()
                eprint(is_full)
                launch = await sync_to_async(self.room.is_game_launch)()
                # eprint("TEST9")
                if is_full:
                    eprint("ROOM FULL")
                    await sync_to_async(self.room.launched)()
                    await self.channel_layer.group_send(self.room.hash, {
                        'type': 'room.full',
                        'left_player': self.room.LeftPlayer4.username,
                        'right_player': self.room.RightPlayer4.username,
                        'second_leftplayer': self.room.SecondLeftPlayer4.username,
                        'second_rightplayer': self.room.SecondRightPlayer4.username,
                        'data': {}
                    })
                    asyncio.create_task(self.game_loop())

    async def receive(self, text_data):
        obj = json.loads(text_data)
        # eprint("receive", obj)
        if (obj["message"] == "stop"):
            await self.close()
        elif(self.user == self.room.LeftPlayer4 or self.user == self.room.SecondLeftPlayer4) :
            if obj["message"] == 'down' and self.map[self.side + 1]["position"][1] < 1:
                # eprint(self.map[self.side + 1]["move"], " hmm ", not self.map[self.side + 1]["move"], "hmm ", self.side + 1)
                self.map[self.side + 1]["move"] = not self.map[self.side + 1]["move"]
                self.map[self.side + 1]["move_direction"] = DOWN
            elif obj["message"] == 'S' and self.map[self.side]["position"][1] < 1:
                # eprint(self.map[self.side]["move"], " hmm ", not self.map[self.side]["move"], "hmm ", self.side)
                self.map[self.side]["move"] = not self.map[self.side]["move"]
                self.map[self.side]["move_direction"] = DOWN
            elif obj["message"] == 'up' and self.map[self.side + 1]["position"][1] > 0:
                # eprint(self.map[self.side + 1]["move"], " hmm ", not self.map[self.side + 1]["move"], "hmm ", self.side + 1 )
                self.map[self.side + 1]["move"] = not self.map[self.side + 1]["move"]
                self.map[self.side + 1]["move_direction"] = UP
            elif obj["message"] == 'W' and self.map[self.side]["position"][1] > 0:
                # eprint(self.map[self.side]["move"], " hmm ", not self.map[self.side]["move"], "hmm ", self.side )
                self.map[self.side]["move"] = not self.map[self.side]["move"]
                self.map[self.side]["move_direction"] = UP
            elif obj["message"] == 'false':
                self.map[self.side + 1]["move"] = False
            else:
                self.map[self.side]["move"] = False
        else:
            if obj["message"] == 'down' and self.map[self.side]["position"][1] < 1:
                # eprint(self.map[self.side]["move"], " hmm ", not self.map[self.side]["move"], "hmm ", self.side)
                self.map[self.side]["move"] = not self.map[self.side]["move"]
                self.map[self.side]["move_direction"] = DOWN
            elif obj["message"] == 'S' and self.map[self.side + 1]["position"][1] < 1:
                # eprint(self.map[self.side + 1]["move"], " hmm ", not self.map[self.side + 1]["move"], "hmm ", self.side + 1)
                self.map[self.side + 1]["move"] = not self.map[self.side + 1]["move"]
                self.map[self.side + 1]["move_direction"] = DOWN
            elif obj["message"] == 'up' and self.map[self.side]["position"][1] > 0:
                # eprint(self.map[self.side]["move"], " hmm ", not self.map[self.side]["move"], "hmm ", self.side )
                self.map[self.side]["move"] = not self.map[self.side]["move"]
                self.map[self.side]["move_direction"] = UP
            elif obj["message"] == 'W' and self.map[self.side + 1]["position"][1] > 0:
                # eprint(self.map[self.side + 1]["move"], " hmm ", not self.map[self.side + 1]["move"], "hmm ", self.side + 1 )
                self.map[self.side + 1]["move"] = not self.map[self.side + 1]["move"]
                self.map[self.side + 1]["move_direction"] = UP
            elif obj["message"] == 'false':
                self.map[self.side]["move"] = False
            else:
                self.map[self.side + 1]["move"] = False
    
    async def disconnect(self, code):
        eprint("disconnect:", self.user)
        if (self.room != None):
            self.room = await database_sync_to_async(GameRoomFour.objects.get)(hash=self.room.hash)
            await sync_to_async(self.room.disconnect)(self.user)
            eprint(await sync_to_async(self.room.count)())
            await self.channel_layer.group_discard(
                self.room.hash, self.channel_name
            )

    async def paddle_move(self, event):
        if event["move"] == 'down' and self.map[event["player"]]["position"][1] < 1:
            # eprint(self.map[event["player"]]["move"], " hmm ", not self.map[event["player"]]["move"])
            self.map[event["player"]]["move"] = not self.map[event["player"]]["move"]
            self.map[event["player"]]["move_direction"] = DOWN
        elif self.map[event["player"]]["position"][1] > 0:
            # eprint(self.map[event["player"]]["move"], " hmm ", not self.map[event["player"]]["move"])
            self.map[event["player"]]["move"] = not self.map[event["player"]]["move"]
            self.map[event["player"]]["move_direction"] = UP 

    async def user_joined(self, event):
        # eprint("MSG")
        await self.send(text_data=json.dumps({
            'event':'user_joined',
            'user': self.user.username,
            **event['data']
        }))

    async def room_full(self, event):
        self.room.Launch = True
        await self.send(text_data=json.dumps({
            'event':'game_wait',
            'user': self.user.username,
            'left_player' : event['left_player'],
            'right_player' : event['right_player'],
            'second_leftplayer': event['second_leftplayer'],
            'second_rightplayer': event['second_rightplayer'],
            **event['data'],
        }))
        
    async def game_loop(self):
        await asyncio.sleep(3)
        await self.channel_layer.group_send(self.room.hash, {
            'type' : 'game.start',
        })
        while (self.map[11]["score"][0] < 2 and self.map[11]["score"][1] < 2 
               and ((self.room.LeftConnect[0]["connect"] or self.room.RightConnect[0]["connect"])
               or (self.room.SecondLeftConnect[0]["connect"] or self.room.SecondRightConnect[0]["connect"]))):
            state = self.get_game_state()
            await self.channel_layer.group_send(self.room.hash, {
                'type':'game.state',
                'state' : state,
                'user': self.user.username,
            })
            await asyncio.sleep(0.016)
        await self.channel_layer.group_discard(self.room.hash, self.channel_name)
        await self.channel_layer.group_send(self.room.hash, {
            'type' : 'game.end',
        })
        ending = self.room
        self.room = None
        await sync_to_async(ending.end_game)(self.map[11]["score"])
        await sync_to_async(ending.reset)()
        eprint(ending.map)

    async def game_start(self, event):
        await self.send(text_data=json.dumps({
            'event' : 'game_start',
            'user': self.user.username,
        }))

    async def game_end(self, event):
        await self.channel_layer.group_discard(
            self.room.hash, self.channel_name
        )
        self.room = None
        await self.send(text_data=json.dumps({
            'event' : 'game_end',
            'user': self.user.username,
        }))
        self.disconnect(0)

    def get_game_state(self):
        ball = self.map[0]
        ball2 = self.map[1]
        ball3 = self.map[2]
        paddleleft = self.map[3]
        paddleleft_2 = self.map[4]
        paddlesecondleft = self.map[5]
        paddlesecondleft_2 = self.map[6]
        paddleright = self.map[7]
        paddleright_2 = self.map[8]
        paddlesecondright = self.map[9]
        paddlesecondright_2 = self.map[10]
        score = self.map[11]

        self.check_ball_collision(ball)
        if self.check_paddle_collision(ball, paddleleft, paddleright):
            self.move_ball(ball)
        elif self.check_paddle_collision_2(ball, paddleleft_2):
            self.move_ball(ball)
        elif self.check_paddle_collision_2(ball, paddleright_2):
            self.move_ball(ball)
        elif self.check_paddle_collision(ball, paddlesecondleft, paddlesecondright):
            self.move_ball(ball)
        elif self.check_paddle_collision_2(ball, paddlesecondleft_2):
            self.move_ball(ball)
        elif self.check_paddle_collision_2(ball, paddlesecondright_2):
            self.move_ball(ball)
        else:
            self.move_ball(ball)

        self.check_ball_collision(ball2)
        if self.check_paddle_collision(ball2, paddleleft, paddleright):
            self.move_ball(ball2)
        elif self.check_paddle_collision_2(ball2, paddleleft_2):
            self.move_ball(ball2)
        elif self.check_paddle_collision_2(ball2, paddleright_2):
            self.move_ball(ball2)
        elif self.check_paddle_collision(ball2, paddlesecondleft, paddlesecondright):
            self.move_ball(ball2)
        elif self.check_paddle_collision_2(ball2, paddlesecondleft_2):
            self.move_ball(ball2)
        elif self.check_paddle_collision_2(ball2, paddlesecondright_2):
            self.move_ball(ball2)
        else:
            self.move_ball(ball2)


        self.check_ball_collision(ball3)
        if self.check_paddle_collision(ball3, paddleleft, paddleright):
            self.move_ball(ball3)
        elif self.check_paddle_collision_2(ball3, paddleleft_2):
            self.move_ball(ball3)
        elif self.check_paddle_collision_2(ball3, paddleright_2):
            self.move_ball(ball3)
        elif self.check_paddle_collision(ball3, paddlesecondleft, paddlesecondright):
            self.move_ball(ball3)
        elif self.check_paddle_collision_2(ball3, paddlesecondleft_2):
            self.move_ball(ball3)
        elif self.check_paddle_collision_2(ball3, paddlesecondright_2):
            self.move_ball(ball3)
        else:
            self.move_ball(ball3)

        self.paddle_move(paddleleft, 1)
        self.paddle_move(paddleleft_2, 2)
        self.paddle_move(paddleright, 1)
        self.paddle_move(paddleright_2, 2)
        self.paddle_move(paddlesecondleft, 2)
        self.paddle_move(paddlesecondleft_2, 1)
        self.paddle_move(paddlesecondright, 2)
        self.paddle_move(paddlesecondright_2, 1)

        ball = self.check_score(ball, score, paddleright, paddleleft)
        ball2 = self.check_score(ball2, score, paddleright, paddleleft)
        ball3 = self.check_score(ball3, score, paddleright, paddleleft)
            
        self.map[0] = ball
        self.map[1] = ball2
        self.map[2] = ball3
        return (json.dumps(self.map))

    def check_score(self, ball, score, paddleright, paddleleft):
        if ball["position"][0] > 1 - paddleright["width"] / 2 :
            ball = ({
                "type": "ball",
                "position": [0.5, 0.5],
                "speed": [SPEED_X, SPEED_Y],
                "radius": RADIUS,
                "move": MOVE2,
            })
            score["score"][0] = score["score"][0] + 1
        elif ball["position"][0] < 0 + paddleleft["width"] / 2 :
            ball = ({
                "type": "ball",
                "position": [0.5, 0.5],
                "speed": [-SPEED_X, SPEED_Y],
                "radius": RADIUS,
                "move": MOVE2,
            })
            score["score"][1] = score["score"][1] + 1
        return (ball)

    def paddle_move(self, paddle, type):
        if type == 1:
            top = 0
            bottom = 0.5
        else :
            top = 0.5
            bottom = 1
        if paddle["move"]:
            if paddle["move_direction"] > 0 and paddle["position"][1] < bottom - PADDLE_HEIGHT:
                paddle["position"][1] += PADDLE_SPEED * paddle["move_direction"]
            elif paddle["move_direction"] < 0 and paddle["position"][1] > top:
                paddle["position"][1] += PADDLE_SPEED * paddle["move_direction"]

    def move_ball(self, ball):
        ball["position"][0] += ball["speed"][0] * ball["move"]
        ball["position"][1] += ball["speed"][1] * ball["move"]

    def check_ball_collision(self, ball):
        if ball["position"][1] + ball["radius"] / 2 + ball["speed"][1] * ball["move"] > 1 or ball["position"][1] + ball["speed"][1] * ball["move"] < 0:
            ball["speed"][1] = -ball["speed"][1]

    def check_paddle_collision(self, ball, paddleleft, paddleright):
        if ball["position"][0] + ball["speed"][0] * ball["move"] > paddleright["position"][0] and ball["position"][1] > paddleright["position"][1] and ball["position"][1] < paddleright["position"][1] + paddleright["height"]:
            ball = self.check_collision_right(ball, paddleright)
            return (True)
        if ball["position"][0] + ball["speed"][0] * ball["move"] < paddleleft["position"][0] + paddleleft["width"] and ball["position"][1] > paddleleft["position"][1] and ball["position"][1] < paddleleft["position"][1] + paddleleft["height"]:
            ball = self.check_collision_left(ball, paddleleft)
            return (True)
        return (False)
    
    def check_paddle_collision_2(self, ball, paddle):
        if (ball["position"][0] < paddle["position"][0] and ball["speed"][0] > 0):
            paddleright = paddle
            if ball["position"][0] + ball["speed"][0] * ball["move"] > paddleright["position"][0] and ball["position"][1] > paddleright["position"][1] and ball["position"][1] < paddleright["position"][1] + paddleright["height"]:
                ball = self.check_collision_right(ball, paddleright)
                return (True)
        elif (ball["position"][0] > paddle["position"][0] and ball["speed"][0] < 0):
            paddleleft = paddle  
            if ball["position"][0] + ball["speed"][0] * ball["move"] < paddleleft["position"][0] + paddleleft["width"] and ball["position"][1] > paddleleft["position"][1] and ball["position"][1] < paddleleft["position"][1] + paddleleft["height"]:
                ball = self.check_collision_left(ball, paddleleft)
                return (True)
        return (False)

    def check_collision_right(self, ball, paddleright):
        relativeImpact = (ball["position"][1] - (paddleright["position"][1] + paddleright["height"] / 2)) / (paddleright["height"] / 2)
        maxAngle = math.pi / 4
        angle = relativeImpact * maxAngle
        ball["speed"][1] = math.sin(angle)
        ball["speed"][0] = -math.cos(angle)
        # eprint("After collision Right: ",  ball["speed"])
        if ball["move"] < MAX_SPEED:
            ball["move"] = ball["move"] * 1.1
            # eprint("ball speed: ", ball["move"])
        return ball

    def check_collision_left(self, ball, paddleleft):
        relativeImpact = (ball["position"][1] - (paddleleft["position"][1] + paddleleft["height"] / 2)) / (paddleleft["height"] / 2)
        maxAngle = math.pi / 4
        angle = relativeImpact * maxAngle
        ball["speed"][1] = math.sin(angle)
        ball["speed"][0] = math.cos(angle)
        # eprint("After collision Left:",  angle, ball["speed"])
        if ball["move"] < MAX_SPEED:
            ball["move"] = ball["move"] * 1.1
            # eprint("ball speed: ", ball["move"])
        return ball

    async def game_state(self, event):
        message = event["state"]
        await self.send(text_data=json.dumps({
            'type':'game_state',
            'message': message,
            'user': self.user.username,
        }))