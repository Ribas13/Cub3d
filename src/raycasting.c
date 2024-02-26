/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/26 23:41:41 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray(t_ray ray)
{
	int	wall_start;
	int	wall_end;
	int	screen_x;
	int	screen_x_end;
	int	screen_y;

	wall_start = calculate_start(ray.distance);
	wall_end = calculate_end(ray.distance);
	screen_x = ray.section;
	screen_x_end = screen_x + 10;
	while (screen_x <= screen_x_end)
	{
		screen_y = 0;
		while (screen_y < 720)
		{
			if (screen_y > wall_start && screen_y < wall_end)
				draw_wall_pixel(screen_x, screen_y, ray.wall_orientation);
			else
				mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
					screen_x, screen_y, BLACK);
			screen_y++;
		}
		screen_x++;
	}
}

char	calculate_wall_orientation(int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (y == map_y * TILE_SIZE)
		return ('N');
	else if (x == map_x * TILE_SIZE)
		return ('W');
	else if (y == ((map_y + 1) * TILE_SIZE) - 1)
		return ('S');
	else if (x == ((map_x + 1) * TILE_SIZE) - 1)
		return ('E');
	return ('0');
}

//Saves the ray distance, and x and y coordinates, ray angle and
//distance and wall orientation
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
	while (i < 128)
	{
		ray = ray_properties(i);
		draw_ray(ray);
		/* if (i == 64)
		{
			printf("--------------------\n");
			printf("ray hit x: %d, ray hit y: %d\n", ray.x, ray.y);
			printf("ray_x / tilesize * tilesize %i\n", ray.x / TILE_SIZE * TILE_SIZE);
			printf("ray_y / tilesize * tilesize %i\n", ray.y / TILE_SIZE * TILE_SIZE);
			printf("ray x + 1 / tilesize * tilesize %i\n", (ray.x + 1) / TILE_SIZE * TILE_SIZE);
			printf("ray y + 1 / tilesize * tilesize %i\n", (ray.y + 1) / TILE_SIZE * TILE_SIZE);
			printf("orientation: %c\n", ray.wall_orientation);
		} */
		angle += ONE_DEGREE / 2;
		i++;
	}
}
