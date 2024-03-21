/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_ver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:41:31 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/21 18:48:20 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	first_intersection_v(t_ray *ray, int x, int y, int og_tile_x, int i)
{
	while (++i < 5000)
	{
		ray->new_x = x + i * ray->a_cos;
		ray->new_y = y + i * ray->a_sin;
		if (ray->new_y < 0
			|| ray->new_y >= (int)ft_data()->map->rows * TILE_SIZE)
			return (true);
		else if (ray->new_x <= 0
			|| ray->new_x > (int)ft_data()->map->cols * TILE_SIZE)
			return (true);
		if ((int)ray->new_x / TILE_SIZE != og_tile_x)
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

bool	second_intersection_v(t_ray *ray, int x, int y, int og_tile_x, int i)
{
	while (++i < 5000)
	{
		ray->new_x = x + i * ray->a_cos;
		ray->new_y = y + i * ray->a_sin;
		if (ray->new_y <= 0
			|| ray->new_y >= (int)ft_data()->map->rows * TILE_SIZE)
			return (true);
		else if (ray->new_x <= 0
			|| ray->new_x >= (int)ft_data()->map->cols * TILE_SIZE)
			return (true);
		if ((int)ray->new_x / TILE_SIZE != og_tile_x)
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

//TO DO: refactor this function
void	set_ray_x_offset(t_ray *ray)
{
	if (ray->angle < 3 * PI / 2 && ray->angle > PI / 2)
	{
		//printf("looking left\n");
		ray->x_offset = -TILE_SIZE;
	}
	else
	{
		//printf("looking right\n");
		ray->x_offset = TILE_SIZE;
	}
}

float	vertical_dist(t_ray ray, int x, int y)
{
	ray.angle = set_angle(ray.angle);
	//ray.found_v_wall = false;
	if (first_intersection_v(&ray, x, y, (x / TILE_SIZE), -1))
		return (calc_h(x, y, ray.new_x, ray.new_y));
	if (second_intersection_v(&ray, ray.new_x, ray.new_y,
			(ray.new_x / TILE_SIZE), -1))
		return (calc_h(x, y, ray.new_x, ray.new_y));
	else
		ray.y_offset = ray.y_hit2 - ray.y_hit1;
	set_ray_x_offset(&ray);
	while (ft_data()->map->map[(int)ray.new_y / TILE_SIZE]
		[(int)ray.new_x / TILE_SIZE] != WALL)
	{
		ray.new_x += ray.x_offset;
		ray.new_y += ray.y_offset;
		if ((int)ray.new_y >= (int)ft_data()->map->rows * TILE_SIZE
			|| (int)ray.new_y <= 0)
			break ;
		else if ((int)ray.new_x >= (int)ft_data()->map->cols * TILE_SIZE
			|| (int)ray.new_x <= 0)
			break ;
		/* mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray.new_x, ray.new_y, RED); */
	}
	return (calc_h(x, y, ray.new_x, ray.new_y));
}
