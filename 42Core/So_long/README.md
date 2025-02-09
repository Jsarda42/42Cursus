# So_long Project

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Lessons Learned](#lessons-learned)

## Introduction

The **So_long** project is a graphical 2D game developed using the `minilibx` library in C. The objective is to navigate a character through a map, collecting items and avoiding obstacles, all while aiming to reach the exit. This project teaches you about graphics programming, event handling, and working with external libraries in C.

You’ll need to create a simple game where the player controls a character's movements on a map grid. The map includes walls, open spaces, collectible items, and an exit. As the player moves through the map, they collect items that may be required to unlock the exit. The project helps develop your skills in managing game logic, rendering images, handling user input, and implementing basic game mechanics.

## Features

- **Map Representation**: The game map is represented as a grid of tiles, where each tile can be a wall, an open space, a collectible item, or the goal.
  
- **Player Movement**: The player can move through the map using keyboard inputs (e.g., arrow keys or WASD) and cannot pass through walls.

- **Collectibles and Goal**: Items are placed on the map, and the player must collect them. The goal is unlocked only once all items have been collected, leading to the next stage or completion.

- **Graphics Rendering**: The `minilibx` library is used to render the game map and the player’s character in a graphical window, where each tile on the map is represented by an image.

- **Collision Detection**: The game handles collision detection, preventing the player from walking through walls or obstacles. The player’s movements are restricted by the map boundaries.

- **Exit Condition**: The game includes an exit condition that is triggered when the player reaches the exit tile, but only after collecting all necessary items.

- **Event Handling**: The player’s movements are controlled through real-time keyboard events. Additionally, the program should handle closing the game window and exiting properly.

- **Error Handling**: Proper error handling for invalid inputs, file loading issues (e.g., map files), or memory allocation failures is essential to ensure smooth gameplay.

## Lessons Learned

1. **Graphics Programming with Minilibx**: The project helped me learn how to use the `minilibx` library for rendering graphics, handling images, and managing windows in a game-like environment.

2. **Game Loop & Event Handling**: I learned how to implement a game loop that continuously checks for player input (keyboard events) and updates the screen accordingly. Handling real-time user inputs for character movement was a key aspect of this project.

3. **Collision Detection**: I understood the importance of detecting collisions between the player and walls or obstacles. This involved checking the player’s coordinates and preventing invalid movements when colliding with walls or map boundaries.

4. **File Parsing and Map Validation**: Parsing the map file to validate its structure (e.g., ensuring it has walls, proper size, and at least one exit) helped me develop skills in handling file data and ensuring correct game configuration.

5. **Memory Management**: Working with dynamic memory allocation and freeing memory after use was crucial in ensuring the program ran efficiently without memory leaks, especially since the game uses several assets (images, map data).

6. **User Experience (UX)**: Designing the player’s interaction with the game required thinking about clear visual feedback (e.g., displaying the character, showing collected items) and intuitive controls to ensure a smooth gaming experience.

7. **Game Design Fundamentals**: Beyond coding, I learned basic game design principles such as creating challenges (collectibles, obstacles) and rewards (exit conditions) that keep the player engaged.

---

