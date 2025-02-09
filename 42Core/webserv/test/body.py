import requests

# Perform a GET request
response_get = requests.get('http://localhost:8081/info.php?key1=value1&key2=value2')
print("\033[94mGET response:\033[0m")
print(response_get.text)
print("\n")

# Perform a POST request
post_data = {'key1': 'value1', 'key2': 'value2'}
response_post = requests.post('http://localhost:8081/info.php', data=post_data)
print("\033[92mPOST response:\033[0m")
print(response_post.text)
print("\n")

# Upload a file
files = {'file': open('body.txt', 'rb')}
response_upload = requests.post('http://localhost:8081/info.php', files=files)
print("\033[93mFile upload response:\033[0m")
print(response_upload.text)
print("\n")
