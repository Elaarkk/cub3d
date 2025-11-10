# Cub3D

This project, part of the 42 School curriculum, is a 3D graphical engine built from scratch in C. It uses the **Raycasting** technique, similar to the engine that powered the classic 1992 game *Wolfenstein 3D*.

The program takes a scene description file (`.cub`) as input, parses it, and launches a real-time 3D environment where the player can navigate a maze. All rendering is done using the 42's MiniLibX library.

## Features

### 1. 3D Raycasting Engine
* **Raycasting:** Implements the raycasting algorithm (a variation of DDA) to find the distance to the nearest wall for every vertical column of the screen.
* **Texture Mapping:** Walls are rendered with `.xpm` textures. The engine correctly determines which texture (North, South, East, or West) to display based on the ray's hit direction.
* **Shading:** "Darkens" the East/West walls to give a better sense of depth and orientation.
* **Floor and Ceiling:** Renders the floor and ceiling as solid colors, defined in the map file.
* **Player View:** The engine renders the world from the player's first-person perspective.

### 2. Scene Parsing
* **`.cub` File Parser:** The program reads a scene file to load all necessary elements.
* **Element Validation:** It parses and validates:
    * **Textures:** Paths to the North (`NO`), South (`SO`), West (`WE`), and East (`EA`) wall textures.
    * **Colors:** RGB values for the Floor (`F`) and Ceiling (`C`).
* **Map Validation:**
    * The map is parsed into a 2D grid.
    * It performs a check (`check_map.c`) to ensure the map is "closed" and surrounded by walls (`1`), preventing the player from escaping.
    * Ensures there is exactly one player starting position (`N`, `S`, `E`, or `W`).

### 3. Player and Controls
* **Movement:** `W` (Forward), `S` (Backward), `A` (Strafe Left), `D` (Strafe Right).
* **Rotation:** `Left Arrow` (Rotate view left), `Right Arrow` (Rotate view right).
* **Sprint:** `Shift``.
* **Exit:** The program can be closed by pressing the `ESC` key or clicking the window's close button.

### 4. Bonus: 
* **Collision:** Basic wall collision is implemented to prevent the player from walking through walls.
* **Minimap**: Renders a 2D top-down minimap in the corner of the screen and shows the player's exact position on the minimap in real-time.

## Compilation

The project uses a `Makefile` that is configured to automatically **clone the `minilibx-linux` library from GitHub** and compile it as a dependency.

To compile the entire project, simply run:
```bash
make
````

## Map File Format (.cub)

The scene file must be formatted correctly:

1. **Elements:** The file must first define the 6 elements (order does not matter, but they must come before the map grid).

````
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0
````

2. **Map Grid:** The file must end with the map grid, composed of:

  - `1`: Wall
  - `0`: Empty space
  - `N`, `S`, `E`, or `W`: Player start position and direction.

````
1111111111
1000N00001
1011001101
1000000001
1111111111
````

## Compilation

The project uses a `Makefile` that is configured to automatically **clone the `minilibx-linux` library from GitHub** and compile it as a dependency.

To compile the entire project, simply run:
```bash
make
````

## Usage

Several example maps are provided in the maps/ directory.

````bash
./cub3D mab.cub
````
