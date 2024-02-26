/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/26 17:47:19 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray(t_ray ray)
{
	//draw a box with x size from x to x + 10
	//the y size is calculated based on the distance from the player and the wall
	//if the distance is bigger, smaller square(from the middle of  the screen)
	//if the distance is smaller, bigger square(from the middle of the screen)
	//screen size is 1280 by 720
	//so for 120 rays in a 60 degree fov, we need to draw 120 boxes
	//120 boxes * 10 pixels = 1200 pixels
	int	wall_start;
	int	wall_end;
	int	screen_x;
	int	screen_x_end;

	//calculate the start and end of the wall based on the distance from the player
	//if a wall is super close, the start and end will be pratically 0 and 720
	//if a wall is super far, the start and end will be pratically 360 and 360 (middle of the screen)
	wall_start = calculate_start(ray.distance);
	wall_end = calculate_end(ray.distance);
	screen_x = ray.section;
	screen_x_end = ray.section + 100;
	while (screen_x < screen_x_end)
	{
		ray.y = 0;
		while (ray.y < 720)
		{
			//draw the vertical line
			if (ray.y >= wall_start && ray.y < wall_end)
				draw_wall_pixel(ray.x, ray.y, ray.wall_orientation);
			//else
				//mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_x, ray.y, BLACK);
			ray.y++;
		}
		screen_x++;
	}
	/* (void)ray;
	int x = 10;
	while (x < 100)
	{
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, 64, RED);
		x++;
	}
	x = 100;
	while (x < 1200)
	{
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, 66, GREEN);
		x++;
	} */
}

char	calculate_wall_orientation(int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	printf("---------\nFuncao calculate_wall_orientation -> ficheiro raycasting.c\n");
	printf("map_x: %d\n", map_x);
	printf("map_y: %d\n", map_y);
	printf("map_x * 64: %d\n", map_x * 64);
	printf("map_y * 64: %d\n", map_y * 64);
	printf("map_x * 64 + 64: %d\n", (map_x * 64) + 64);
	printf("map_y * 64 + 64: %d\n", (map_y * 64) + 64);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("---------\n");
	//return ('N');
	if (x == map_x * 64)
		return ('W');
	if (x == ((map_x * 64) + 64))
		return ('E');
	if (y == map_y * 64)
		return ('N');
	if (y == ((map_y * 64) + 64))
		return ('S');
	return ('0');
}

//Saves the ray distance, and x and y coordinates, ray angle and distance and wall orientation
t_ray	ray_properties(int i)
{
	t_ray	ray;

	ray.angle = ft_data()->player->dir - (FOV / 2) + (i * ONE_DEGREE / 2);
	ray.section = i * 10;
	ray.distance = ray_dist(ray.angle, 5000, ft_data()->player->pos.x,
			ft_data()->player->pos.y);
	ray.x = ft_data()->player->pos.x + ray.distance * cos(ray.angle);
	ray.y = ft_data()->player->pos.y + ray.distance * sin(ray.angle);
	ray.wall_orientation = calculate_wall_orientation(ray.x, ray.y);
	return (ray);
}

//function to draw cast rays around the player in a 60 degree fov
//still need to add more rays, 60 is not enough
//we need to add a a check for where the ray hits the wall
//if its on top of the player its a north wall, 
//if its on the right its a east wall
//if its on the bottom its a south wall, if its on the left its a west wall

//might need to allocate memory for the rays
void	cast_rays(void)
{
	float	angle;
	int		i;
	t_ray	ray;


	i = 0;
	angle = ft_data()->player->dir - (FOV / 2);
	//if only middle ray dir is desired to debug, pass 60 as arg to ray_properties
	//and set angle to ft_data()->player->dir
	while (i < 120)
	{
		ray = ray_properties(i);
		//meti a funcao que diz a orientacao da parede a dar sempre return N para fazer debug
		draw_ray(ray);
		//draw_ray(ray_properties(i));
		//for (int j = 40; j < 80; j++)
		//{
			//mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, i * 10, j, RED);
		//}
		angle += ONE_DEGREE / 2;
		i++;
	}
}
