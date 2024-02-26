/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:17 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/26 23:05:02 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	calculate_start(int distance)
{
	return (360 - (360 - distance));
}

int	calculate_end(int distance)
{
	return (360 + (360 - distance));
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
