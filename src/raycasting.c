/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/25 19:20:21 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ray_dist(float angle, int length, int x, int y)
{
	int	i;
	int	new_x;
	int	new_y;

	i = 0;
	while (i < length)
	{
		new_x = x + i * cos(angle);
		new_y = y + i * sin(angle);
		if (ft_data()->map->map[(int)new_y / TILE_SIZE]
			[(int)new_x / TILE_SIZE] == WALL)
			break ;
		i++;
	}
	//determine the direction of the wall (north, south, east, west)
	//each wall is contained inside a 64 by 64 square, so we need to determine
	//which face of the square the ray hit
	//if the ray hits the top of the square, its a north wall
	//if the ray hits the right of the square, its a east wall
	//if the ray hits the bottom of the square, its a south wall
	//if the ray hits the left of the square, its a west wall
	//we need to return the distance from the player to the wall and update the
	return (i);
}

//given a degree and distance, draw a square shape
//if the distance is bigger, smaller square(from the middle of  the screen)
//if the distance is smaller, bigger square(from the middle of the screen)
//each section is 60 pixels wide by 540 tall
//there is a total of 17 sections
void	draw_box(int degree, int distance)
{
	int	start_x;
	int	start_y;
	int	middle;
	int	i;
	int	wall_height;

	middle = 540 / 2;
	start_x = degree * 10;
	wall_height = (540 / distance) * 50;
	start_y = middle - wall_height / 2;
	while (start_y < middle + wall_height / 2)
	{
		i = 0;
		while (i < 10)
		{
			if (distance < 300)
				mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, start_x + i,
					start_y, WHITE);
			else
				mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, start_x + i,
					start_y, GREEN);
			i++;
		}
		start_y++;
	}
}

//function to draw cast rays around the player in a 60 degree fov
//still need to add more rays, 60 is not enough
//we need to add a a check for where the ray hits the wall
//if its on top of the player its a north wall, if its on the right its a east wall
//if its on the bottom its a south wall, if its on the left its a west wall
void	cast_rays(void)
{
	float	angle;
	int		i;


	i = 0;
	angle = ft_data()->player->dir - (FOV / 2);
	while (i < 120)
	{
		//x = ft_data()->player->pos.x;
		//y = ft_data()->player->pos.y;
		//draw_box(i, ray_dist(angle, 5000, ft_data()->player->pos.x, ft_data()->player->pos.y));
		ray_dist(angle, 5000, ft_data()->player->pos.x,
			ft_data()->player->pos.y);
		angle += 0.0174533 / 2;
		i++;
	}
}
