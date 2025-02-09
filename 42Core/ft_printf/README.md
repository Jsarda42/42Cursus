# ft_printf Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

The **ft_printf** project is designed to implement a simplified version of the `printf` function in C. It is part of the 42 curriculum and aims to develop a deep understanding of variadic functions, format specifiers, and the underlying mechanisms of the C standard library. This project challenges students to implement the ability to format and print different data types, similar to the standard `printf`, but with a custom approach and optimizations.

In this project, you'll learn how to manage different data types (such as integers, strings, and pointers) and implement formatting options (such as padding, precision, and alignment) from scratch.

## Features

- **Variadic Function**: Implementing `ft_printf` as a variadic function, accepting multiple arguments of different types.
- **Format Specifiers**: Handling of basic format specifiers such as `%s`, `%d`, `%i`, `%c`, `%u`, `%x`, `%X`, and `%p`.
- **Width and Precision**: Supporting width and precision modifiers for formatting strings, integers, and other data types.
- **Custom Conversion**: Converting numbers to different bases (e.g., decimal to hexadecimal) with proper formatting (upper/lowercase, padding, etc.).
- **Error Handling**: Ensuring proper handling of invalid format specifiers and edge cases.

## Lessons Learned

1. **Variadic Functions**: The primary lesson from this project was learning how to handle variadic functions, which allow you to accept a variable number of arguments. Understanding how to iterate through different argument types was crucial.

2. **Format Specifiers and Conversion**: This project gave me an in-depth understanding of how format specifiers work in C, as well as how to implement conversions such as integer-to-string, decimal-to-hexadecimal, etc.

3. **Precision and Width Handling**: Implementing width and precision for various data types made me better understand the flexibility of formatting strings, numbers, and other types in C. Handling edge cases such as very large or very small numbers, as well as special characters, was key.

---

