
# OpenGL 3D experiment


# Huw's Game Engine
This is a playground for experimenting with 3D rendering, OpenGL, Artificial Intelligence, Physics and more.

## Setup
Open project file in Qt Creator, setup kit and build.

## Commands
Press ``` ` ``` to open command editor. Currently we have "Bob" and "Dave" NPCs available to interact with.

| Command   | Description                        | Template                 |
|-----------|------------------------------------|--------------------------|
| pushState | Pushes/adds state to specific NPC. | pushState {NAME} {STATE} |
| popState  | Pops/removes state from NPC.       | popState {NAME}          |
| getState  | Gets top state of stack.           | getState {NAME}          |
| setHealth | Sets health to NPC.                |setHealth {NAME{ {VALUE}  |
| getHealth | Gets health of NPC.                | getHealth {NAME}         |
| moveTo    | Move to x,y                        | moveto {NAME} {X} {Y}    |

### States
 - idle10
 - attack
 - flee
 - patrol
 - alert

## Todo

 - ~~Textures~~
 - ~~Diffuse lighting~~
 - ~~Ambient lighting~~
 - ~~Lighting (Phong or Gourand, phong chosen)~~
 - ~~Map (for objects)~~
 - ~~Object collision~~
 - ~~Cubemap~~
 - ~~Basic 3D collision~~
  - ~~Pathfinding~~
 - ~~WASD~~
 ~~Main menu~~
 - AI **(in progress)**
 -  ~~OpenGL push/pop ~~
 -   ~~Better movement ~~
 -  Object loader **(in progress)**
 - Picture frames
 - Software Culling
 - Game intro
 - Grass
 - Mechanics
 - Fun
 - Better texture format
 - Trees
 - Mouse control


## Dependencies

 - SDL 2
 - FreeGlut 3

Run commands in Terminal below to install dependencies.

```
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev mesa-utils freeglut3-dev freeglut3 freeglut3-dev
```
