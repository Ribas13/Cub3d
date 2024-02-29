/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/29 01:04:55 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_texture_color(t_tiles_img *texture, int texture_x_offset, int texture_y)
{
	int	color;
	int	*arr;

	arr = (int *)texture->addr;
	color = arr[texture_y * texture->width + texture_x_offset];
	return color;
}

void	draw_wall(int wall_start, int wall_end, int screen_x, t_tiles_img *texture, t_ray ray)
{
	int		screen_y;
	double	y_offset;
	int		texture_y;
	int		color;

	screen_y = 0;
	while (screen_y < SCREEN_HEIGHT)
	{
		if (screen_y >= wall_start && screen_y < wall_end)
		{
			y_offset = (double)(screen_y - wall_start) / (wall_end - wall_start);
			texture_y = (int)(y_offset * texture->height);
			color = get_texture_color(texture, ray.texture_x_offset, texture_y);
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_x, screen_y, color);
		}
		else
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_x, screen_y, BLACK);
		}
		screen_y++;
	}
}

void	draw_ray(t_ray ray)
{
	int wall_start = calculate_start(ray.distance);
	int wall_end = calculate_end(ray.distance);
	int screen_x = ray.section;
	int screen_x_end = ray.section + 10;

	while (screen_x <= screen_x_end)
	{
		draw_wall(wall_start, wall_end, screen_x, ray.texture, ray);
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

t_tiles_img *get_texture(char wall_orientation)
{
	if (wall_orientation == 'N')
		return (ft_data()->tiles->wall);
	else if (wall_orientation == 'E')
		return (ft_data()->tiles->wall);
	else if (wall_orientation == 'S')
		return (ft_data()->tiles->space);
	else if (wall_orientation == 'W')
		return (init_tiles_img(ft_data()->mlx_ptr,SPACE_TILE));
	return (ft_data()->tiles->space);
}

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
	ray.texture = get_texture(ray.wall_orientation);
	if (ray.wall_orientation == 'N' || ray.wall_orientation == 'S')
		ray.texture_x_offset = (ray.x % TILE_SIZE) * (double)ray.texture->width / TILE_SIZE;
	else // ray.wall_orientation is 'E' or 'W'
		ray.texture_x_offset = (ray.y % TILE_SIZE) * (double)ray.texture->width / TILE_SIZE;
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
