import requests

def test_body_sizes(url, sizes):
    for size in sizes:
        body = 'a' * size
        response = requests.post(url, data=body)
        print(f"Size: {size}, Status Code: {response.status_code}, Response: {response.text}")

if __name__ == "__main__":
    url = "http://localhost:8080/"
    sizes = [10, 100, 1000, 1001, 10000, 100000]
    test_body_sizes(url, sizes)