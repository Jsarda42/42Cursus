# Cube 3D Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

The **Cube 3D** project is a 3D game where we use **raycasting** to render a 3D environment, similar to the classic **Wolfenstein** game. The goal is to create a first-person perspective game where the player navigates through a maze-like environment. This involves simulating a 3D world on a 2D screen using raycasting techniques to calculate the visibility of objects in the environment.

Raycasting is a technique used to project 3D walls and floors onto a 2D plane by casting rays from the player’s viewpoint, determining which walls are in the player’s line of sight, and rendering them accordingly. This project introduces concepts in graphics programming and game development, especially how to create a 3D effect in a 2D environment.

## Features

- **Raycasting**: The core of the project is raycasting, where rays are cast from the player's viewpoint to calculate the intersection with walls in the game world. This allows the simulation of a 3D environment on a 2D screen.
  
- **First-Person Perspective**: The player navigates through the environment using keyboard inputs (typically WASD or arrow keys). The player's viewpoint is updated based on their movements and rotation.

- **Rendering the 3D Environment**: The game renders 3D walls and floor textures based on the distance from the player to the walls. The closer a wall is, the taller it appears on the screen, creating the illusion of depth.

- **Player Movement**: The player can move forward, backward, and rotate left or right within the game world. The controls simulate a first-person shooter (FPS) experience.

- **Map Generation**: The game world is built using a 2D grid representing walls and empty spaces. This map is used to generate the 3D environment seen by the player during gameplay.

- **Basic Lighting and Shading**: The project may include simple lighting effects, such as darkening walls further away from the player or simulating light sources within the environment.

- **Minimal Game Mechanics**: While the project focuses on rendering the environment, simple game mechanics like movement and collision detection are implemented.

- **Window and Event Handling**: The program uses a graphics library (e.g., **MinilibX**) for creating the game window, handling events (like key presses), and rendering the game’s graphics in real-time.

## Lessons Learned

1. **Raycasting**: The project provided a deep dive into raycasting, teaching me how rays are cast from the player’s viewpoint, how to detect intersections with walls, and how to render the environment based on those calculations. Raycasting is a fundamental technique for creating 3D environments in early FPS games.

2. **3D Rendering on a 2D Screen**: I learned how to simulate a 3D world using raycasting on a 2D plane, understanding how distance, angle, and view determine how objects are displayed. The project helped me grasp the concept of "3D on 2D" rendering.

3. **Player Controls and Movement**: Implementing player movement and rotation using keyboard inputs helped me understand how to update a player's position and view in a virtual environment.

4. **Collision Detection**: I learned how to handle basic collision detection by checking ray intersections with the walls of the game world. This was critical for ensuring that the player’s movement was restricted by the environment.

5. **Performance Optimization**: Raycasting requires efficient calculations to ensure smooth gameplay. I optimized ray calculations and rendering to prevent performance bottlenecks, such as unnecessary recalculations or slow frame rates.

6. **Game Development Basics**: This project taught me the basics of game development, including handling real-time user input, updating game states (player movement, game world), and rendering graphics dynamically.

7. **Understanding Game Engines**: The project gave me insights into how game engines work at a low level, especially in rendering 3D environments without relying on full 3D models, using basic techniques like raycasting instead.

8. **Graphics Programming**: I gained valuable experience in low-level graphics programming, working with pixel manipulation, and rendering environments from a mathematical perspective.

---



