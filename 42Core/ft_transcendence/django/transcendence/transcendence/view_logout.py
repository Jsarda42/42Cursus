from django.shortcuts import redirect
from django.contrib.auth import logout

def logout_view(request):
	# Log the user out by calling the logout function from Django's auth module
	logout(request)
		
	# Redirect the user to the 'home' page after successful logout
	return redirect('home')
