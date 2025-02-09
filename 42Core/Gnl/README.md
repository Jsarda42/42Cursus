# get_next_line Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

The **get_next_line** project is part of the 42 curriculum and focuses on implementing a function that reads a line from a file descriptor, returning it one line at a time. This project allows students to practice working with file input/output, memory management, and buffers. The goal is to create a function that behaves like the `get_next_line` system call in C, but without using the standard library's version.

This project will help you understand how to manage dynamic memory allocation and buffers efficiently, as well as how to handle edge cases such as multiple file descriptors and varying line lengths.

## Features

- **Reading from File Descriptors**: The function reads from any file descriptor (e.g., standard input, a file, etc.), extracting one line at a time.
- **Dynamic Memory Allocation**: Efficient memory allocation for each line that is read and stored, ensuring proper handling of memory throughout the process.
- **Edge Case Handling**: Properly handling various edge cases such as empty lines, lines that are too large to fit in the buffer, and end-of-file scenarios.
- **Buffer Management**: The project challenges you to manage a buffer efficiently, ensuring that leftover data is preserved for future reads.

## Lessons Learned

1. **File Input/Output**: This project helped me understand how to work with file descriptors and read data from files in a low-level manner, without relying on higher-level functions like `fgets` or `getline`.

2. **Memory Management**: Implementing `get_next_line` involved managing memory carefully, especially since each line read requires dynamic memory allocation. Learning how to allocate, resize, and free memory efficiently was crucial for this project.

3. **Buffering and Efficiency**: Handling large files or very large lines required careful buffer management to ensure the program doesn't waste memory or miss any data. I learned how to manipulate buffers to manage data and handle leftovers efficiently.

4. **Edge Case Handling**: The project taught me the importance of considering edge cases, such as reading an empty file, handling file reading errors, or reading past the end of a file. Handling these cases gracefully is critical in real-world programming.

---

