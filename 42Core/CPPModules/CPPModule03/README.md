# CPP Module 03 Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

**CPP Module 03** introduces **inheritance** in C++. Inheritance is one of the core concepts of **Object-Oriented Programming (OOP)**, and it allows you to create new classes based on existing ones. This enables the reuse of code, facilitates the creation of hierarchies, and promotes **modularity** and **extensibility** in your programs.

In this module, you will learn how to use inheritance to model real-world relationships and understand how derived classes inherit attributes and behaviors from base classes. You'll also study the different types of inheritance, such as **single inheritance**, **multiple inheritance**, and **multilevel inheritance**, and how to manage access control with **public**, **protected**, and **private** inheritance.

## Features

- **Single Inheritance**: Learn about **single inheritance**, where a derived class inherits from a single base class. This is the simplest form of inheritance, where the derived class extends the functionality of the base class.

- **Multiple Inheritance**: Understand **multiple inheritance**, where a derived class inherits from more than one base class. This allows the derived class to have the characteristics of multiple classes but also introduces potential complexity, such as the **diamond problem**.

- **Multilevel Inheritance**: Explore **multilevel inheritance**, where a class is derived from another class, which is itself derived from another class. This creates a chain of inheritance, where each class can build upon the functionality of its ancestor class.

- **Access Specifiers**: Study the use of **access specifiers** (i.e., **public**, **protected**, and **private**) in inheritance. Learn how the inheritance mechanism affects the visibility of base class members in the derived class.

- **Constructor and Destructor Inheritance**: Learn how constructors and destructors are inherited in derived classes. Understand the rules for calling base class constructors and destructors in derived class constructors.

- **Method Overriding**: Discover how derived classes can **override** methods of the base class to provide their own implementation, allowing for **runtime polymorphism**. This is crucial for implementing polymorphic behavior in object-oriented programs.

- **The `virtual` Keyword**: Understand the use of the **`virtual` keyword** to allow method overriding in derived classes and to enable **runtime polymorphism**. This keyword ensures that the correct method is called even when using base class pointers or references.

- **`protected` and `private` Inheritance**: Learn the difference between **protected** and **private** inheritance, and when to use each to control the accessibility of base class members.

## Lessons Learned

1. **Understanding Inheritance**: I learned how **inheritance** allows a derived class to inherit attributes and methods from a base class. This enables me to create more specialized classes based on general ones, reusing code and improving efficiency.

2. **Single Inheritance**: I explored **single inheritance**, where a derived class is based on one base class. This type of inheritance is straightforward and easy to understand, and it allows me to build on top of existing classes to add specialized behavior.

3. **Multiple Inheritance**: I understood the concept of **multiple inheritance**, where a derived class can inherit from more than one base class. While powerful, I learned that this can introduce challenges, such as the **diamond problem**, which needs to be managed carefully in C++.

4. **Multilevel Inheritance**: I learned how **multilevel inheritance** works, where a class inherits from another class that is itself derived from yet another class. This creates a hierarchy of classes and allows me to build more complex relationships between classes.

5. **Access Specifiers and Inheritance**: I gained an understanding of how **access specifiers** affect the inheritance of base class members. I learned that **public inheritance** allows full access to base class members, while **protected** and **private inheritance** restrict access in different ways.

6. **Constructors and Destructors in Inheritance**: I learned how constructors and destructors are inherited in C++, and how the **constructor chaining** works. In derived classes, constructors from the base class are automatically called, and destructors are executed in reverse order during object destruction.

7. **Method Overriding and Polymorphism**: I explored **method overriding** and how it allows derived classes to provide their own implementations of methods from base classes. I learned how **runtime polymorphism** is achieved when base class pointers or references are used to call overridden methods.

8. **The `virtual` Keyword and Polymorphism**: I learned the importance of the **`virtual` keyword** in enabling **runtime polymorphism**. This ensures that the correct method from the derived class is called, even when using base class pointers or references.

9. **Managing Inheritance with `protected` and `private`**: I discovered the use of **protected** and **private inheritance**, which helps to limit the accessibility of base class members to the derived class and can be useful in certain design scenarios.

10. **Code Reusability and Extensibility**: By applying inheritance, I improved my ability to write **modular**, **reusable**, and **extensible** code. I now understand how to use inheritance to create flexible and maintainable class hierarchies.

---



