/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_hor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:40:03 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/21 18:48:31 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	first_intersection_h(t_ray *ray, int x, int y, int og_tile_y, int i)
{
	while (++i < 5000)
	{
		ray->new_x = x + i * ray->a_cos;
		ray->new_y = y + i * ray->a_sin;
		if (ray->new_x < 0
			|| ray->new_x > (int)ft_data()->map->cols * TILE_SIZE)
			return (true);
		else if (ray->new_y < 0
			|| ray->new_y > (int)ft_data()->map->rows * TILE_SIZE)
			return (true);
		if ((int)ray->new_y / TILE_SIZE != og_tile_y)
		{
			if (ft_data()->map->map[(int)ray->new_y / TILE_SIZE]
				[(int)ray->new_x / TILE_SIZE] == WALL)
				return (true);
			else
			{
				ray->x_hit1 = ray->new_x;
				ray->y_hit1 = ray->new_y;
				break ;
			}
		}
		/* mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray->new_x, ray->new_y, WHITE); */
	}
	return (false);
}

bool	second_intersection_h(t_ray *ray, int x, int y, int og_tile_y, int i)
{
	while (++i < 5000)
	{
		ray->new_x = x + i * ray->a_cos;
		ray->new_y = y + i * ray->a_sin;
		if (ray->new_x < 0
			|| ray->new_x > (int)ft_data()->map->cols * TILE_SIZE)
			return (true);
		else if (ray->new_y < 0
			|| ray->new_y > (int)ft_data()->map->rows * TILE_SIZE)
			return (true);
		if ((int)ray->new_y / TILE_SIZE != og_tile_y)
		{
			if (ft_data()->map->map[(int)ray->new_y / TILE_SIZE]
				[(int)ray->new_x / TILE_SIZE] == WALL)
				return (true);
			else
			{
				ray->x_hit2 = ray->new_x;
				ray->y_hit2 = ray->new_y;
				break ;
			}
		}
		/* mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray->new_x, ray->new_y, GREEN); */
	}
	return (false);
}

void	set_ray_y_offset(t_ray *ray)
{
	if (ray->angle > 0 && ray->angle < PI)
		ray->y_offset = 32;
	else
		ray->y_offset = -32;
}

/* Right now we can walk the ray until the first two horizontal line collisions
Now we need to save both of the intersection coordinates and compare them to
save the offset*/
//still need to correctly set the cols and rows of the map
float	horizontal_dist(t_ray ray, int x, int y)
{
	ray.angle = set_angle(ray.angle);
	//ray.found_h_wall = false;
	if (first_intersection_h(&ray, x, y, (y / TILE_SIZE), -1))
		return (calc_h(x, y, ray.new_x, ray.new_y));
	if (second_intersection_h(&ray, ray.new_x, ray.new_y,
			(ray.new_y / TILE_SIZE), -1))
		return (calc_h(x, y, ray.new_x, ray.new_y));
	else
		ray.x_offset = ray.x_hit2 - ray.x_hit1;
	set_ray_y_offset(&ray);
	while (ft_data()->map->map[(int)ray.new_y / TILE_SIZE]
		[(int)ray.new_x / TILE_SIZE] != WALL)
	{
		ray.new_x += ray.x_offset;
		ray.new_y += ray.y_offset;
		if ((int)ray.new_x / TILE_SIZE > (int)ft_data()->map->cols
			|| (int)ray.new_x < 0)
			break ;
		else if ((int)ray.new_y / TILE_SIZE > (int)ft_data()->map->rows
			|| (int)ray.new_y < 0)
			break ;
		/* mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray.new_x, ray.new_y, BLACK); */
	}
	return (calc_h(x, y, ray.new_x, ray.new_y));
}
