/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/27 15:02:09 by diosanto         ###   ########.fr       */
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
	ray.distance = normalize_angle(ray);
	return (ray);
}
/* 
bool	stop_threads(void)
{
	if (ft_data()->keys->esc == true)
	{
		return (true);
	}
	return (false);
}

void	*render_section(void *threads)
{
	int			ray;
	int			ray_end;
	float		angle;
	t_render	*threads2;

	threads2 = (t_render *)threads;
	ray = threads2->starting_ray;
	ray_end = ray + 32;
	angle = ft_data()->player->dir - (FOV / 2) + (ray * ONE_DEGREE / 2);
	ray = threads2->starting_ray;
	while (ray < ray_end)
	{
		draw_ray(ray_properties(ray));
		angle += ONE_DEGREE / DEGREE_MULTIPLIER;
		ray++;
	}
	return (NULL);
}

//void	work_threads()

void	start_thread(void)
{
	t_render	threads[4];
	int			ray;
	int			starting_ray;

	ray = -1;
	starting_ray = 0;
	ft_data()->thread_array = threads;
	while (++ray < 4)
	{
		threads[ray].id = ray;
		threads[ray].starting_ray = starting_ray;
		pthread_create(&threads[ray].thread, NULL,
			render_section, &threads[ray]);
		starting_ray += 32;
	}
}

void	end_thread(void)
{
	int	ray;

	ray = -1;
	while (++ray < 4)
	{
		pthread_join(ft_data()->thread_array[ray].thread, NULL);
	}
} */

void	cast_rays(void)
{
	int		ray;
	int		sections;
	float	angle;

	ray = -1;
	angle = ft_data()->player->dir - (FOV / 2);
	sections = (FOV * (180 / PI)) * DEGREE_MULTIPLIER;
	while (++ray <= sections)
	{
		draw_ray(ray_properties(ray));
		angle += ONE_DEGREE / DEGREE_MULTIPLIER;
	}
}
