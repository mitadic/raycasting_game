# Raycasting-powered engine
This is a raycasting engine for 2D→3D projection, inspired by 1992 Wolfenstein

## Demo
| ![final](https://github.com/user-attachments/assets/5ba101ee-86f9-431d-8fb4-247075fb0208) |
|:---:|
| Engine in action with custom neon textures |

## Installation

> [!NOTE]
> These installation steps assume availability of x11 and clang or gcc

### Installation steps

1. Clone the repository; enter the created directory.

        $ git clone https://github.com/mitadic/raycasting_game; cd raycasting_game

2. Optional: tweak the settings manually in `cub3d.h` before compiling

       // Settings 
       # define SCREEN_W 800
       # define SCREEN_H 600
       # define PLAY_FPS 60
       # define ROT_SPEED_FEED 0.015
       # define MOV_SPEED_FEED 0.0125

4. Compile

        $ make

### Usage

Run the app with a map of your choosing.
```bash
./cub3d maps/full.cub
```

### Customization
Add your custom maps/*.cub files with specifications for
1. maps (`1`: walls, `0`: walkable tiles, `N|W|S|E`: player position and orientation)
2. textures (`.xpm` format images only)
3. floor & ceiling colors (RGB)



## 🔬📚 Gains
The goal of the project was to recreate the then revolutionary tech behind Wolfenstein 3D from scratch. Although the engine is natively 2D, it renders a first-person 3D perspective by simulating a 3D environment on a 2D map.

### The basic idea
We start with a 2D grid-based map where each cell represents walls (1) or empty space (0).
Using raycasting, we simulate the player's perspective by casting rays in different directions and calculating wall distances.
Each ray represents a "line of sight" from the player’s position in a specific direction. As each ray moves forward, it checks for wall intersections on the map grid. We display different wall heights based on distance to give a depth illusion. The closer a wall is, the taller it appears.
As the player moves around and rotates, the 3D render updates, showing only what the player "sees" based on the rays cast.

### The math
The project requires understanding vectors, trigonometry, and distance calculations.
Before we dive into the math, let's go over a few important concepts
#### FOV (field of view)
defines how wide the player's visible world is in terms of angles. A wider FOV means fewer rays but a zoomed-in view.
#### Player angle
The direction the player is facing, crucial for determining where rays are cast.
#### Ray angle
The angle for each individual ray cast relative to the player's position, calculated based on the player angle and FOV.
#### Grid-based optimization
Since walls are aligned with grid cells, we implemented the DDA Alorithm that only checks for walls at grid intersections, allowing us to optimize wall hit detection. 
The algorithm determines the distance from the player to the wall by stepping through the grid either horizontally or vertically, depending on which direction the ray is moving.

### DDA algorithm breakdown
1) Calculate the initial side distances (side_dist_x, side_dist_y), which represent the distance from the player to the nearest grid boundary in both the X and Y directions.
2) Calculate the step size that represent the distance the ray has to travel along each axis (X or Y) to move from one grid line to the next. Use the ray’s direction and step size (delta_dist_x, delta_dist_y) to increment the ray’s position step-by-step until it intersects a wall. 
3) Once a wall is hit (grid value equals '1'), we calculate the exact intersection point between ray and the grid by determining whether the ray crosses a vertical or horizontal grid line first, adjusting for the player's position and the ray's direction to find the precise coordinates. Finally, we calculate the distance from the player to the wall at the intersection point, first using the Pythagorean theorem, then refining the distance by adjusting for overshoot caused by stepping past grid lines.



## Credits & Feedback

If you have any feedback, feel free to reach out to the authors.

| Team          | <img src="https://github.githubassets.com/assets/GitHub-Mark-ea2971cee799.png" alt="gh_logo.png" width="15" height="15"/> | <img src="https://cdn3.iconfinder.com/data/icons/web-ui-3/128/Mail-2-512.png" alt="email_icon.jpg" width="15" height="15"/> | Responsibilities |
| ------------- | ------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------- | :--- |
| Jasmin Nguyen | [@JasminNguyen](https://github.com/JasminNguyen)                                                                              | jasnguye@student.42.fr                                                                                                  | maths, rendering, QoL features, performance optimization
| Milos Tadic   | [@mitadic](https://github.com/MilosTadic01)                                                                                         | mitadic@student.42.fr                                                                                             | map parsing, minilibX integration, testing, visuals

We thank our peers of 42 Berlin for their limitless drive for discovery and for their rigor and precision in providing feedback. We are likewise grateful to 42 Berlin itself for fostering a culture of inclusive excellence.

## License

[CC0 1.0 Universal](/LICENSE.txt)

