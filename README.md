# Boids

A flocking simulation written in C++ with SFML 3 for rendering and CMake as the build system.

## Overview

Boids is a classic artificial life simulation in which each agent follows a few simple local rules: alignment, cohesion, and separation. The simulation starts with a randomized flock, updates their motion in real time, and renders each boid as a directional triangle.

The project is designed to be easy to follow and extend. The simulation loop, flocking logic, and drawing code are separated into a small set of focused classes, which keeps behavior tuning and visual changes independent.

## Features

- Classic boids behavior: alignment, cohesion, and separation
- Real-time flock simulation with large numbers of boids
- Randomized initial positions and velocities
- Screen wrapping so the flock continues across boundaries
- Velocity clamping to keep movement within a natural speed range
- Perception radius visualization for selected agents
- Reset the flock with Space
- Close the application with Escape

## Design

The codebase is intentionally modular and split into a few clear responsibilities:

- Simulation (`Simulation.h/.cpp`) - creates the SFML window, manages the main loop, handles input, and owns the simulation state.
- Engine (`Engine.h/.cpp`) - contains the pure flocking logic and updates positions and velocities based on the boids rules.
- Renderer (`Renderer.h/.cpp`) - is responsible only for drawing the boids and their perception circles.

This separation keeps the simulation logic independent from rendering. A change in flock behavior can be made in the Engine without affecting drawing code, and visual changes can be made in the Renderer without altering the movement rules.

## Controls

| Input | Action |
|--------|--------|
| Space | Reset the flock |
| Escape | Close the application |

## Building

Requires CMake 3.28+ and C++17. SFML 3.1.0 is fetched automatically with `FetchContent`, so there is no manual installation step.

```bash
cmake -B build -S .
cmake --build build
```

This builds the executable into `build/bin`.

## Tech stack

- C++
- SFML
- CMake
