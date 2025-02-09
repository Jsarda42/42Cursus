# Minishell Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

**Minishell** is a project where you implement a simple shell program that mimics some of the basic functionalities of a Unix shell. The goal is to create a command-line interface that accepts user input, parses the commands, and executes them. The shell should handle various features such as piping, redirection, environment variables, and built-in commands.

This project focuses on system programming, process management, and parsing, requiring knowledge of Unix processes and file descriptors. By implementing Minishell, you learn how shells work under the hood, including how they interact with the operating system.

## Features

- **Command Parsing**: The shell should be able to correctly parse user input into commands, arguments, and flags. This includes handling quotes, escaping characters, and splitting commands into arguments.

- **Executing Commands**: The shell must execute external programs using the `execve` system call and manage processes via `fork`. You will handle basic commands like `ls`, `echo`, `pwd`, and more.

- **Pipes**: The shell must handle piping between commands, such as `command1 | command2`. The output of the first command should become the input of the second command.

- **Redirection**: The shell should support input and output redirection, like `command > file` (output redirection) or `command < file` (input redirection).

- **Environment Variables**: The shell must allow the user to access and manipulate environment variables (e.g., `echo $PATH`), and also support exporting new variables (e.g., `export VAR=value`).

- **Built-in Commands**: Implement basic built-in commands such as `cd`, `exit`, and `echo`. The shell should handle these commands internally without invoking external programs.

- **Process Management**: The shell should create child processes using `fork()` and wait for their completion using `waitpid()`. It should also handle multiple background processes and proper cleanup.

- **Signal Handling**: The shell must handle signals, such as `SIGINT` (Ctrl+C), to ensure that it behaves properly when the user interrupts a process.

- **Error Handling**: Proper error messages should be displayed when commands fail (e.g., "command not found"), and the shell should handle edge cases gracefully.

## Lessons Learned

1. **System Programming**: The biggest takeaway from this project was learning how shells work at a low level. I gained hands-on experience with system calls such as `fork()`, `execve()`, and `waitpid()` for process creation and management.

2. **Command Parsing and Tokenization**: Implementing the command parser and tokenizer taught me how to break down complex user input into structured data. This process involved handling delimiters, quotes, escaping characters, and more.

3. **Handling Redirection and Pipes**: I learned how to handle file descriptors for redirection and how to set up pipes between processes to redirect input/output. This required a deep understanding of how Unix handles streams and file descriptors.

4. **Environment Variables**: I learned how to manage environment variables, including reading, modifying, and exporting them within the shell. Understanding how to interact with the environment using `getenv()` and `setenv()` was crucial.

5. **Process Synchronization**: Handling multiple processes, including background processes and managing child processes, gave me insight into how processes are scheduled and managed in Unix-like systems.

6. **Signal Handling**: The project helped me understand signal handling in a shell environment, especially the importance of handling signals like `SIGINT` to ensure the shell doesn't crash unexpectedly when the user interrupts processes.

7. **Error Handling and Robustness**: Implementing error handling and edge case management helped me understand how to make the shell robust. The project reinforced the need for detailed error messages and graceful failure management.

8. **Memory Management**: As with any C project, proper memory management was crucial, especially when dealing with dynamically allocated strings and buffers for parsing and executing commands. I learned to carefully manage memory allocation, deallocation, and avoiding memory leaks.

---

