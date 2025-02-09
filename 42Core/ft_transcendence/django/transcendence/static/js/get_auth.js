export const getAuth = async () => {
	try {
		const response = await fetch("api/user-profile/");
		const data = await response.json();
		return {
			data,
			username: data.username,
			profileImageUrl: data.profile_image_url
		};
	} catch (error) {
		console.error("Error fetching user:", error);
	}
  };