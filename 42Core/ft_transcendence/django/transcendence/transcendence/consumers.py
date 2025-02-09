from channels.generic.websocket import AsyncWebsocketConsumer
from channels.db import database_sync_to_async
import sys
import json

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

class LogsConsumer(AsyncWebsocketConsumer):
    
    async def connect(self):
        if self.scope["user"].is_anonymous:
            eprint("logs socket anonymous so refused")
            self.user = None
            self.close()
        else:
            self.nbconnect = 0
            self.user = self.scope["user"]
            await setConnection(self.user, True)
            await self.channel_layer.group_add(
                self.user.username, self.channel_name
            )
            await self.channel_layer.group_send(self.user.username,{
                'type' : 'new.connection',
            }) 
            await self.accept()

    async def new_connection(self, event):
        self.nbconnect += 1
        eprint("number of connection:", self.nbconnect)
        if (self.nbconnect > 1):
            await self.send(text_data=json.dumps({
                'event' : 'two_connection',
            }))

    async def disconnect(self, close_code):
        if not self.scope["user"].is_anonymous:
            await setConnection(self.user, False)
        
@database_sync_to_async
def setConnection(user, bool):
    user.connect.is_online = bool
    user.connect.save()