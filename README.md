<!-- ![image](https://github.com/Ribas13/Cub3d/assets/108695074/0ae7f3ba-1f34-40dd-adca-9d7d1ae24c5c)<br> -->
# CUB3D - a raycasting game in C 🕹️

 This project is a barebones clone of the famous game from the 90's, **Wolfenstein 3D**
 <p align="center">
  <img width="520" height="300" src="https://github.com/Ribas13/Cub3d/assets/108695074/0ae7f3ba-1f34-40dd-adca-9d7d1ae24c5c">
</p> 

### The goal with this project was to not only create the engine that runs the game and renders each frame, but also how to optimize the calculations for each frame in a way that allows the CPU to run the game smoothly on almost every machine. (Even from the 90's 😛)

 ![wolfenstein3d](https://github.com/Ribas13/Cub3d/assets/108695074/cc355da3-7bae-409f-8e2f-da52ca83ead0)

 ## Key Concepts

 - ### Raycasting <br>
   <br>This is the key concept of the whole project, in order to simulate a 3d world, we have to calculate the distance of several points from the player location in order to create depth.

   - (Insert picture of player with rays coming out of it)
   <br>
- ### Raycasting Engine <br>
  <br>When we combine the raycaster with a method to draw lines to the screen, we are able to create a player viewport. By casting a ray for each vertical line of the screen (for a 1280x720 resolution, we cast 1280 rays on every loop)
   ```C
   int	raycasting(void)
   {
	 t_ray		*ray;
	 int			screen_slice;
   
	 screen_slice = 0;
	 ray = ft_data()->ray;
	 while (screen_slice < SCREEN_WIDTH) // Iterate on every vertical line on the screen
	 {
		ray_properties(ray, ft_data()->player, screen_slice); // Get this ray's properties (initial coordinates, etc.)
		setup_algo(ray, ft_data()->player);                        // Run the algorithm to set the wall slice orientation (North, South, West or East)
		dda_algo(ray, ft_data()->map);                             // and calculate the height of the line to be drawn to the screen (if the ray hits
		get_line_height(ray, ft_data()->player);                   // a wall that's further away from the player, the line needs to be smaller in height
		ray->wall_orientation = set_ray_orientation(ray);
		textures_updates(ray, get_texture(ray->wall_orientation), screen_slice);
		screen_slice++;
	 }
	 return (0);
   }
   ```

- ### The DDA Algorithm <br>
<br>With the many "first attempts" at this project's biggest challenge(figuring out an algorithm efficient enough to not be deadly slow) I had to learn something that now seems obvious to me.<br><br>
**Repeating trigonometric calculations needlessly really slows down the program**<br>
Who would've guessed, right?<br>
<br>
So once I had figured an algorithm that was able to consistently draw to the screen, I started to tackle optimization by reducing the amount of calculations I was doing.
I managed to do that by following these steps:
- Remove repetetive sin and cos that didn't change with every iteration.
- Implemented multi-threading

After doing all that, the program was running a bit smoother, but it still wasn't as smooth as I wanted. I continued to develop other parts of the program until I ran into a huge problem.

When I rendered textures do the walls, the game would get super slow.
This is because all the optimizations I had done, had been applied to an algorithm that wasn't going to be able to support the amount of calculations we needed it to do. (we are talking about modern harware, so you can imagine what it would look like on an older machine)

Up until then my algorithm was simply getting the distance of the ray hit coordinates from the player, meaning it was iterating through every coordinate of the ray slope.
Long story short, for a ray with a distance of 40, I would do 40 iterations. For a ray with a distance of 1000, I would do 1000 iterations, this was incredibly inefficient.

> ***This is where the DDA Algorithm comes in.***

Instead of calculating the distance to the wall, unit by unit. We just calculate the distance to the first horizontal and vertical hits on the grid. After that we know the delta for each component of the ray (x and y) and we can just interate
until we hit the next horizontal and vertical lines and keep adding that difference until we hit a wall.

This meant that at the best cases, we would hit a wall in just a couple of iterations, and at the worst the iterations would be not much more than the size of the map (meaning not much more than 25 iterations on a 25x25 map, for example).

Besides the performance improvements that this offered, there was also the fact that I no longer had to correct the fisheye effect, meaning even more processing savings.
With all these performance improvements, I decided to remove the multithreading in order to see the potential of the algorithm. I was amazed, I could easily get more than 60 frames per second without multithreading, we now had a lot of performance headroom to add whatever we wanted, meaning the base game engine was done for now!

## 🥳 The base game is finished for now, so we can add whatever we want to it. 🎉
### (Add gif of base engine gameplay) 
You can add:
- Enemies
- Doors
- Collectibles
- Portals
- Whatever your imagination desires :)
