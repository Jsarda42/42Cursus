# CPP Module 09 Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

**CPP Module 09** is designed to help you understand the different **containers** available in C++. Containers are fundamental data structures that allow you to store and organize data in an efficient and convenient way. In this module, you will learn about the **Standard Template Library (STL)** containers such as **vectors**, **lists**, **queues**, **stacks**, **maps**, and **sets**. Each container has its own strengths and weaknesses depending on the use case and operations required.

By the end of the module, you will have a strong understanding of how to use these containers and the key differences between them. You'll also learn when to choose one container over another, based on factors like access speed, insertion/removal efficiency, and memory usage.

## Features

- **Vector**: Understand how the **vector** container works, which is a dynamic array that can resize itself automatically. Learn about its fast access to elements and efficient push_back operations, as well as its limitations when it comes to inserting or removing elements from the middle or front.

- **List**: Learn about the **list** container, which implements a **doubly linked list**. This container allows efficient insertion and removal of elements from both ends but sacrifices random access to elements, making it less suited for scenarios that require fast random access.

- **Deque**: Explore the **deque** (double-ended queue) container, which allows efficient insertions and deletions at both ends, but with slower random access compared to a vector. Deques are useful when you need both efficient access and modification at both ends of the sequence.

- **Stack**: Understand how the **stack** container operates as a **LIFO (Last In, First Out)** structure, where elements are inserted and removed from only one end. Learn when to use a stack in situations that require backtracking or function call management.

- **Queue**: Learn about the **queue** container, which works as a **FIFO (First In, First Out)** structure, where elements are added to the back and removed from the front. This is commonly used for task scheduling and handling data in order.

- **Priority Queue**: Study the **priority queue** container, where each element has a priority, and elements are dequeued in order of their priority. This is typically used in scheduling algorithms and data processing where order matters based on priority.

- **Set**: Explore the **set** container, which stores unique elements in a sorted order. Sets are useful when you need to ensure there are no duplicates in your collection and want to quickly check for membership.

- **Map**: Understand how the **map** container works, which stores key-value pairs and allows fast lookups, insertions, and deletions based on keys. This is ideal for situations where you need an efficient way to map one value to another, such as storing settings or configurations.

- **Unordered Containers**: Learn about **unordered containers** like **unordered_set** and **unordered_map**, which store elements in an unordered fashion and offer faster average access times compared to their ordered counterparts but without maintaining any order among the elements.

- **Container Operations**: Learn the common operations supported by these containers, such as **insertions**, **deletions**, **searching**, and **accessing elements**. You'll also learn about iterators, which allow you to traverse and manipulate elements in the containers in a standardized manner.

## Lessons Learned

1. **Understanding Different Containers**: I learned about various types of **containers** in C++, including **vectors**, **lists**, **deques**, **stacks**, **queues**, **sets**, and **maps**. I now understand when to use each type based on my specific needs, such as whether I need efficient random access, fast insertions and deletions, or ordered data.

2. **Choosing the Right Container**: I gained the ability to choose the right container for the task at hand. For example, if I need fast access and resizing capabilities, a **vector** is ideal. For quick insertions and deletions from both ends, a **deque** is appropriate. For maintaining unique elements in sorted order, a **set** is the best option.

3. **Vector and List Performance**: I learned the trade-offs between **vectors** and **lists**. While **vectors** provide fast access to elements, **lists** offer efficient insertions and deletions at both ends, making them more suitable for certain dynamic operations.

4. **Stack and Queue Use Cases**: I learned how to use **stacks** and **queues** for managing data in a LIFO or FIFO manner, respectively. These containers are perfect for tasks like managing function calls (stack) or scheduling tasks (queue).

5. **Priority Queues**: I explored **priority queues**, which ensure that the highest-priority elements are dequeued first. This is useful for tasks like job scheduling and handling real-time data.

6. **Set and Map Operations**: I now understand how **sets** and **maps** work, storing unique values in sorted order or key-value pairs, respectively. I learned how to efficiently perform operations like **search**, **insert**, and **delete** in these containers.

7. **Unordered Containers**: I learned the benefits of **unordered containers**, which allow faster average access times by not maintaining any order among elements. I now know when to use **unordered_set** and **unordered_map** for faster lookups when order isn't required.

8. **Container Operations with Iterators**: I gained experience with **iterators**, which provide a unified way to traverse through different types of containers. Iterators make it easier to write generic code that can work with any container type.

9. **Memory Management and Efficiency**: I learned about the **memory management** considerations for different containers. For example, **vectors** resize dynamically but may involve reallocations, while **lists** allocate memory for each element individually. I now know how to choose containers based on performance and memory usage.

10. **Optimizing Code with Containers**: By mastering the use of **containers**, I can now optimize my code by selecting the most appropriate container based on its strengths and weaknesses. This helps me achieve efficient operations while keeping the code maintainable and scalable.

---

