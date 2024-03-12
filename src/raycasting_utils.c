/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:17 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/12 17:35:00 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Fisheye effect correction
float	normalize_angle(t_ray ray)
{
	float	normalized;

	normalized = sqrt(pow(ray.x - ft_data()->player->pos.x, 2)
			+ pow(ray.y - ft_data()->player->pos.y, 2))
		* cos(ray.angle - ft_data()->player->dir);
	return (normalized);
}

int	calculate_start(float distance)
{
	int	projected_height;
	int	start;

	if (distance < MIN_DISTANCE)
		distance = MIN_DISTANCE;
	projected_height = (int)((720 / 2) * 60 / distance);
	start = (720 - projected_height) / 2;
	return (start);
}

int	calculate_end(float corrected_distance)
{
	int	projected_height;
	int	end;

	if (corrected_distance < MIN_DISTANCE)
		corrected_distance = MIN_DISTANCE;
	projected_height = (int)((720 / 2) * 60 / corrected_distance);
	end = (720 + projected_height) / 2;
	return (end);
}

float	ray_dist(float angle, int length, int x, int y)
{
	float	dist;
	int		new_x;
	int		new_y;
	float	a_cos;
	float	a_sin;

	dist = 0;
	a_cos = cos(angle);
	a_sin = sin(angle);
	while (dist < length)
	{
		new_x = x + dist * a_cos;
		new_y = y + dist * a_sin;
		if (ft_data()->map->map[new_y / TILE_SIZE]
			[new_x / TILE_SIZE] == WALL)
			break ;
		dist += 1;
	}
	return (dist);
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
