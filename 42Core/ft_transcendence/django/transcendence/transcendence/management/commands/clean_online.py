from transcendence.models import Connected
from django.core.management.base import BaseCommand


class Command(BaseCommand):
    arg=''
    help='clean online status'

    def handle(self, *args, **options):
        online = Connected.objects.all()
        for a in online:
            a.is_online = False
            a.save()
