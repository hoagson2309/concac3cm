
---
title: Maze Solver - Software Design Report
author: Son Cao
date: 29 May 2025
---

# Software Design Report – Maze Mapping

## 1. Introduction

This document describes the design of the Maze Mapping system implemented in C++. It focuses on the architectural understanding and class design using System Context and Class Diagrams, created with PlantUML.

The project implements real-time maze exploration using a `MazeMap` class that interacts with ultrasonic sensors and motor controllers to build and maintain a 2D grid representation of walls and visited cells as the robot navigates the environment.

## 2. System Context Diagram

The system consists of a Maze Mapping core that processes sensor data and controls robot movements to construct the maze representation.

<center style="margin-bottom:20px">

```plantuml
skinparam defaultTextAlignment center
scale 250 height

storage "Maze Mapping\n(Core System)" as Core #white;line.dashed;line:darkgrey;

Rectangle "Ultrasonic Sensor" as Sensor
Rectangle "Motor Driver" as Motor
Rectangle "Maze Representation" as Maze
Rectangle "Position Tracking" as Position

Sensor --> Core : distance_cm
Core --> Motor : moveForward(),\nturnLeft(),\nturnRight()
Core --> Maze : updateWalls(x,y,direction),\nmarkVisited(x,y)
Core --> Position : updatePosition()
Position --> Core : current_x,\ncurrent_y,\ncurrent_heading
Maze --> Core : wall_data,\nvisited_status
```

<figcaption>Figure 1. System Context Diagram of the Maze Solver.</figcaption>
</center>

## 3. Class Diagram

This diagram shows the structure of the `MazeMap` class and its relationships with sensor and motor components.

<center style="margin-bottom:20px">

```plantuml
scale 200 height

class Position {
    + int x
    + int y
    + Direction dir
}

enum Direction {
    NORTH
    EAST
    SOUTH
    WEST
}

class Cell {
    + bool wall[4] // N,E,S,W
    + bool visited
}

class USSensor {
    + readSensor() : float
}

class MotorDriver {
    + Car_Run(command, speed)
}

class MazeMap {
    + MazeMap(sensor, motor)
    + initMaze()
    + turnLeft()
    + turnRight()
    + moveForward()
    + updateWalls()
    + printMaze()
    + getMaze() : Cell[][]
    - sensor : USSensor*
    - motor : MotorDriver*
    - maze : Cell[MAZE_SIZE][MAZE_SIZE]
    - robotPos : Position
}

MazeMap --> Position
MazeMap --> Cell
MazeMap --> Direction
MazeMap --> USSensor
MazeMap --> MotorDriver
```

<figcaption>Figure 2. Class diagram of MazeSolver and its dependencies.</figcaption>
</center>

## 4. Implementation Summary

- **MazeMap::updateWalls()** is the core method that:
  - Takes ultrasonic readings from front, left, and right directions
  - Converts relative sensor data to absolute wall positions using current orientation
  - Updates the maze grid with wall positions using:
```cpp
if (front < 10) maze[y][x].wall[robotPos.dir] = true;
if (left < 10) maze[y][x].wall[(robotPos.dir+3)%4] = true; 
if (right < 10) maze[y][x].wall[(robotPos.dir+1)%4] = true;
```
- Movement control methods:
    - `turnLeft()/turnRight()`: Execute 90° turns while updating orientation
    - `moveForward()`: Updates position while checking maze boundaries
- Key dependencies:
    - `USSensor::readSensor()` for distance measurements
    - `MotorDriver::Car_Run()` for physical movement control
    - Internal Position tracking for dead reckoning navigation
## 5. Conclusion

This report outlines the architectural and class design of the Maze Mapping system using UML diagrams created in PlantUML. The design successfully separates:
    1. **Physical interaction** (sensor input and motor control)
    2. **Spatial representation** (maze grid structure)
    3. **Navigation logic** (position tracking and movement)

- Key design features include:
    - Fixed 5×5 grid representation (MAZE_SIZE)
    - Four-way wall detection (N/E/S/W)
    - Visited-cell tracking for exploration management
    - 10cm threshold for wall detection

- The modular design allows for future enhancements such as:
    - Integration with pathfinding algorithms
    - Dynamic maze size adaptation
    - Improved position tracking using additional sensors
