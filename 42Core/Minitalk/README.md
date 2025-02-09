# Minitalk Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

The **Minitalk** project is part of the 42 curriculum, focusing on inter-process communication (IPC) and signal handling in Unix-based systems. The goal of this project is to implement a communication system between two programs using signals (specifically `SIGUSR1` and `SIGUSR2`) to transmit data between them.

The project challenges students to work with signals at a low level, learning how processes can communicate through a limited communication mechanism. This requires a deep understanding of process management, signal handling, and binary data manipulation in C.

## Features

- **Signal-based Communication**: Implementing communication between processes using Unix signals (`SIGUSR1` and `SIGUSR2`) to send and receive data.
- **Sender and Receiver Programs**: Creating two separate programs: a sender that encodes and sends messages, and a receiver that decodes and displays the received messages.
- **Binary Data Representation**: Encoding characters into binary format to send each bit of data via signals, and decoding them on the receiver side.
- **Error Handling**: Ensuring the programs can handle signal transmission errors and timing issues gracefully.
- **Multi-Character Messaging**: Supporting the transmission of strings or messages that consist of multiple characters, encoded and decoded one bit at a time.
- **Process Communication**: Implementing a communication system between two different processes running concurrently on the system.

## Lessons Learned

1. **Signal Handling**: A major lesson from this project was learning how to handle Unix signals (`SIGUSR1` and `SIGUSR2`) and how they can be used to communicate between processes. I learned the importance of proper signal synchronization and handling during communication.

2. **Low-Level Communication**: The project taught me how processes can communicate without traditional methods (like pipes or shared memory). Instead, signals allow communication at a much lower level, which I had to manage manually.

3. **Binary Data Encoding**: I gained experience in working with binary data. Encoding characters as binary, sending them bit-by-bit through signals, and decoding them required a good understanding of how data is represented and manipulated at the bit level.

4. **Process Management**: This project gave me a deeper understanding of how processes run concurrently and how they can be coordinated and synchronized using signals. I also learned how to handle the timing and order of signals.

5. **Error and Edge Case Handling**: The project required careful attention to edge cases, such as handling the possibility of missing or out-of-order signals. I learned how to add mechanisms to ensure reliable communication, even under imperfect conditions.

6. **Efficiency in Communication**: Optimizing the transmission of messages and ensuring that the process communication was fast and reliable was an important challenge. I learned to manage system resources effectively when handling multiple signals and ensuring minimal delays.

---

