# Webserv Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

The **Webserv Project** is a C++ project that simulates the basic functionality of a **web server**. This project aims to teach the fundamentals of how web servers work, including handling HTTP requests and responses, parsing URLs, and managing different types of content such as HTML, CSS, and images. It simulates the core logic behind a simple server like **Nginx** or **Apache**, but with a simplified design to help understand the essential components.

In this project, you will implement basic server functionalities like **listening** for incoming client connections, **parsing HTTP requests**, serving static files, and returning appropriate **HTTP responses**. It is a great way to grasp the core concepts of web servers, such as **multi-threading**, **sockets**, **protocols**, and **server-client communication**.

## Features

- **HTTP Request Parsing**: Learn how to parse **HTTP requests** from incoming client connections. This includes reading the request line, headers, and body, and understanding how web browsers and servers communicate using the **HTTP protocol**.

- **Handling Multiple Connections**: Implement **multi-threading** to handle multiple client connections simultaneously. This will ensure that the server can process requests from multiple users at the same time without blocking any one connection.

- **Serving Static Files**: Serve static content such as **HTML**, **CSS**, **JavaScript**, and image files (e.g., **JPG**, **PNG**, **GIF**) based on the incoming request. Learn how to read and return files to the client based on their requested URLs.

- **HTTP Response Creation**: Generate appropriate **HTTP responses** with the correct status codes (e.g., **200 OK**, **404 Not Found**, **405 Method Not Allowed**) and serve the requested files or error messages. 

- **URL Parsing**: Implement **URL parsing** to extract relevant parts of the URL from the incoming request, such as the path to the file or directory. Learn how to handle routing and determine which file to serve based on the requested URL.

- **Configuration Handling**: Create and manage a configuration file that allows for server customization, such as setting the root directory, allowed methods, and server parameters. Understand how configuration files affect server behavior and improve flexibility.

- **Handling HTTP Methods**: Implement support for various HTTP methods such as **GET**, **POST**, **DELETE**, etc. Learn how to handle different request types and respond accordingly.

- **Error Handling**: Implement error handling for invalid requests, such as **404 Not Found** for missing files or **405 Method Not Allowed** for unsupported HTTP methods. Provide appropriate error messages to clients.

- **Logging**: Implement logging of incoming requests and responses, allowing for easy monitoring of server activity and troubleshooting.

- **Concurrency**: Use **multi-threading** to handle multiple requests at once, ensuring that each client connection is handled independently and that the server remains responsive under load.

## Lessons Learned

1. **Understanding HTTP Requests and Responses**: I learned how to parse and process **HTTP requests** to extract relevant information like headers, URLs, and request methods. I also learned how to generate and format proper **HTTP responses** for clients.

2. **Socket Programming**: I gained experience with **socket programming**, learning how to create a server that listens on a specific port for incoming connections, accepts those connections, and sends data back to the clients.

3. **Multi-threading and Concurrency**: I implemented **multi-threading** to handle multiple simultaneous client connections. This taught me how web servers manage many requests at once without blocking or crashing.

4. **File Handling**: I learned how to serve **static files** to clients based on URL requests. This included reading files from the filesystem and serving them over a network connection with the correct **HTTP headers**.

5. **Error Handling in Servers**: I understood the importance of proper **error handling** in web servers. I learned to return appropriate error codes (e.g., **404**, **405**) and display custom error pages when necessary.

6. **Configuration Management**: I gained knowledge of how **configuration files** are used in web servers to set parameters like the server root, allowed methods, and directories. This allows for easy customization and flexibility in server behavior.

7. **URL Routing**: I learned about **URL parsing** and how to extract and handle URLs in a way that allows a server to return the correct file or content based on the URL path.

8. **Logging for Monitoring**: I implemented **logging** of incoming requests, which gave me valuable insight into how web servers can track requests and monitor server activity. This is essential for debugging and improving performance.

9. **Client-Server Communication**: I improved my understanding of **client-server communication** over TCP/IP, which is crucial for building distributed systems and networked applications.

10. **Performance and Scalability**: I realized the importance of **scalability** and **performance** in building a server. By learning how to handle multiple requests concurrently with **multi-threading**, I now know how web servers can scale and perform under high traffic loads.

---

