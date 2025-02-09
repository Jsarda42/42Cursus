# Libft Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
4. [Lessons Learned](#lessons-learned)

## Introduction

Libft is one of the foundational projects in the 42 curriculum. It consists of creating a personal library of functions in C, which are commonly used in various other programming projects. The goal of this project is to demonstrate your understanding of fundamental C concepts, such as memory management, string manipulation, and working with file input/output, all while building a versatile set of functions that can be reused across other projects.

In this project, you will write several functions that are usually provided by standard libraries like `libc`. The challenge here is to implement them from scratch, reinforcing your understanding of how low-level operations work.

## Features

- **Memory management functions**: Functions like `malloc`, `free`, and custom memory-related operations.
- **String manipulation functions**: Implementations of `strlen`, `strcpy`, `strcmp`, `strcat`, and others that allow manipulating and working with strings.
- **Character handling functions**: Custom implementations of `isalpha`, `isdigit`, `toupper`, and `tolower` for character testing and conversion.
- **Utility functions**: Includes helpful utilities such as `itoa`, `memcpy`, and `memset`, to simplify tasks commonly used in programming.
- **Modularity**: Each function is self-contained, and you can easily extend or modify the library to suit your needs for future projects.

## Lessons Learned

1. **Deep Understanding of C Functions**: I gained a much deeper understanding of how C's standard library functions work under the hood. This includes dealing with memory allocation, string manipulation, and character handling without relying on built-in functions.
   
2. **Memory Management**: A key takeaway from this project was learning how to manage memory manually in C. Understanding how to allocate and free memory properly is essential for building efficient applications.

3. **Attention to Detail**: Writing these functions from scratch required careful attention to detail to ensure they were both efficient and reliable. Implementing functions like `ft_strcpy` or `ft_memcpy` taught me the importance of understanding pointer manipulation and edge cases.

4. **Modular Design**: This project helped me understand how to create reusable, modular code that can be easily adapted for future projects. Building a personal library of functions that can be reused makes your coding workflow more efficient.

5. **Error Handling**: Writing functions from scratch also involved learning how to handle errors and edge cases more effectively, such as null pointers or invalid inputs, which are critical in real-world development.
