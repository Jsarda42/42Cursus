# CPP Module 05 Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

**CPP Module 05** introduces **exception handling** in C++. In C++, exceptions provide a way to handle errors or unusual situations that occur during program execution. Instead of writing error-checking code everywhere, exceptions allow you to **throw** an exception when an error occurs and **catch** it elsewhere in your program.

This module focuses on the **Try/Catch** block for handling exceptions, as well as creating your own custom exceptions. By understanding how to use exceptions properly, you will be able to write more robust, maintainable, and error-resistant programs. The module also covers how to create your own exception classes for more specific error handling needs.

## Features

- **Exception Handling Basics**: Learn the core concepts of **exception handling** in C++, including the syntax for `try`, `catch`, and `throw`. Understand how exceptions can be used to handle errors that occur during the execution of your program.

- **`try` Block**: The `try` block is used to wrap code that might throw an exception. If an exception is thrown, the program jumps to the corresponding `catch` block to handle the error.

- **`catch` Block**: The `catch` block catches exceptions thrown by the `try` block. Learn how to catch different types of exceptions and how to define multiple `catch` blocks to handle different types of errors in a clean and organized manner.

- **Throwing Exceptions**: Learn how to **throw exceptions** in your program when an error or unexpected situation occurs. Understand how to throw standard exceptions, as well as how to create your own custom exceptions.

- **Standard Exceptions**: Explore the different types of **standard exceptions** in C++ provided by the C++ Standard Library, such as `std::exception`, `std::out_of_range`, `std::invalid_argument`, and more. Learn when and how to use these built-in exceptions.

- **Custom Exceptions**: Learn how to create your own **custom exception classes** to handle specific types of errors in your application. This allows you to make your exception handling more specific to your program's needs.

- **Exception Propagation**: Understand how exceptions are propagated through function calls and how to catch exceptions at different levels of your application.

- **Exception Safety**: Learn how to write **exception-safe** code that ensures resources like memory or file handles are properly managed, even if an exception occurs.

## Lessons Learned

1. **Understanding Try/Catch Syntax**: I learned the basic syntax of exception handling in C++ using `try`, `catch`, and `throw`. This structure allows me to handle runtime errors in a clear and organized way.

2. **Throwing Exceptions**: I gained experience with **throwing exceptions** in my programs. Throwing exceptions allows me to handle errors at higher levels of the program, making my code cleaner and easier to maintain.

3. **Catching Different Types of Exceptions**: I learned how to use **multiple `catch` blocks** to handle different types of exceptions. By using specific exception types, I can ensure that the correct handling mechanism is applied to different kinds of errors.

4. **Custom Exception Classes**: I learned how to create custom exception classes, allowing me to define my own error messages and exception types. This is especially useful when dealing with domain-specific errors that aren't covered by the standard library.

5. **Exception Propagation**: I explored how exceptions propagate through function calls and how they can be caught at various levels in the call stack. This is essential for managing errors that occur in deeply nested function calls.

6. **Standard Exceptions**: I explored the standard exception classes provided by the C++ Standard Library, such as `std::out_of_range`, `std::invalid_argument`, and `std::logic_error`, and learned when it’s appropriate to use each.

7. **Writing Exception-Safe Code**: I learned the importance of writing exception-safe code, especially when dealing with resource management (like memory allocation or file handling). This ensures that resources are cleaned up properly, even in the event of an exception.

8. **Improving Code Robustness**: By integrating exception handling, I was able to make my programs more **robust** and **resilient** to errors. Exception handling allows my programs to handle unexpected situations gracefully without crashing or producing undefined behavior.

---

