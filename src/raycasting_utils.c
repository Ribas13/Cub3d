/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:17 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/26 17:41:34 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//calculates the starting y coordinate of the wall on the screen based on the distance from the player
//if the wall is closer, the starting coordinate is closer to the top of the screen
//if the wall is further, the starting coordinate is closer to the middle of the screen
int	calculate_start(int distance)
{
	//if (distance < 100)
		//return (0);
	//printf("wall start: %d\n", 720 / 2 - distance / 2);
	return (720 / 2 - distance / 2);
}

int	calculate_end(int distance)
{
	//if (distance < 100)
		//return (720);
	//printf("wall end: %d\n", 720 / 2 + distance / 2);
	return (720 / 2 + distance / 2);
}

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
	return (i);
}

void	draw_wall_pixel(int x, int y, char wall_orientation)
{
	if (wall_orientation == 'N')
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, NORTH_WALL);
	else if (wall_orientation == 'E')
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, EAST_WALL);
	else if (wall_orientation == 'S')
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, SOUTH_WALL);
	else if (wall_orientation == 'W')
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, WEST_WALL);
	else if (wall_orientation == '0')
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, GREEN);
}
