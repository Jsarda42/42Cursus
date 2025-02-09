export async function checkAuth() {
	try {
		const response = await fetch("/api/check-auth/", {
			credentials: 'same-origin', // Ensure cookies are sent
		});

		if (response.status === 200) {
			return {
				isAuthenticated: true
			};
		} else if (response.status === 401) {
			// Token might have expired; try to refresh it
			const newTokenResponse = await refreshAuthToken();
			if (newTokenResponse.status === 200) {
				// Token was refreshed, retry the original check
				return await checkAuth();
			} else {
				return { isAuthenticated: false };
			}
		} else {
			return { isAuthenticated: false };
		}
	} catch (error) {
		console.error("Error checking authentication status:", error);
		return { isAuthenticated: false };
	}
}

async function refreshAuthToken() {
	try {
		const response = await fetch("/api/refresh-token/", {
			credentials: 'same-origin'

		});

		return response;
	} catch (error) {
		console.error("Error refreshing authentication token:", error);
		return { status: 500 }; // Server error
	}
}
