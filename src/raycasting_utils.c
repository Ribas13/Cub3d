/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:17 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/28 23:37:44 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Fisheye effect correction
/* float	normalize_angle(t_ray ray)
{
	float	normalized;
	float	distance;

	normalized = fabs(ft_data()->player->dir - ray.angle);
	if (normalized < 0)
		normalized += 2 * PI;
	if (normalized > 2 * PI)
		normalized -= 2 * PI;
	distance = ray.distance;
	normalized = distance * cos(normalized);
	return (normalized);
} */

float	normalize_angle(t_ray ray)
{
	float	corrected_distance;

	corrected_distance = ray.distance * cos(ft_data()->player->dir - ray.angle);
	if (corrected_distance < 0.1)
		corrected_distance = 0.1;
	return (corrected_distance);
}

int	calculate_start(float distance)
{
	int	projected_height;
	int	start;

	if (distance < MIN_DISTANCE)
		distance = MIN_DISTANCE;
	projected_height = (int)((720 / 2) * 60 / distance);
	start = (720 - projected_height) / 2;
	if (start < 0)
		start = 0;
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
	if (end > 720)
		end = 720;
	return (end);
}

float	ray_dist(float angle, int length, int x, int y)
{
	float	dist;
	int		new_x;
	int		new_y;

	dist = 0;
	while (dist < length)
	{
		new_x = x + dist * cos(angle);
		new_y = y + dist * sin(angle);
		if (ft_data()->map->map[(int)new_y / TILE_SIZE]
			[(int)new_x / TILE_SIZE] == WALL)
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
