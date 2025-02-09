from django.conf import settings
from django.shortcuts import redirect
from decouple import config

def redirect_to_42(request):
	oauth_url = (
		"https://api.intra.42.fr/oauth/authorize?"
		f"client_id={settings.OAUTH_42_CLIENT_ID}&"
		f"redirect_uri={settings.OAUTH_42_REDIRECT_URI}&"
		"response_type=code&scope=public"
	)
	return redirect(oauth_url)
