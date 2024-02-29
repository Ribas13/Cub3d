/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/29 01:07:13 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_texture_color(t_tiles_img *texture, int texture_x_offset, int texture_y)
{
	int	color;
	int	*arr;

	arr = (int *)texture->addr;
	color = arr[texture_y * texture->width + texture_x_offset];
	return (color);
}

void	draw_wall(int wall_start, int wall_end, int screen_x, t_tiles_img *texture, t_ray ray)
{
	int		screen_y;
	double	y_offset;
	int		texture_y;
	int		color;

	screen_y = 0;
	(void)ray;
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

t_tiles_img	*get_texture(char wall_orientation)
{
	if (wall_orientation == 'N')
		return (init_tiles_img(ft_data()->mlx_ptr,WALL_TILE));
	else if (wall_orientation == 'E')
		return (init_tiles_img(ft_data()->mlx_ptr,WALL_TILE));
	else if (wall_orientation == 'S')
		return (init_tiles_img(ft_data()->mlx_ptr,SPACE_TILE));
	else if (wall_orientation == 'W')
		return (init_tiles_img(ft_data()->mlx_ptr,SPACE_TILE));
	return (ft_data()->tiles->north);
}

t_ray	ray_properties(int i)
{
	t_ray	ray;

	ray.angle = ft_data()->player->dir - HALF_FOV + (i * HALF_DEGREE);
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

void	cast_rays(void)
{
	int		ray;
	int		sections;
	float	angle;

	ray = -1;
	angle = ft_data()->player->dir - HALF_FOV;
	sections = (FOV * (180 / PI)) * DEGREE_MULTIPLIER;
	while (++ray <= sections)
	{

		draw_ray(ray_properties(ray));
		angle += ONE_DEGREE / DEGREE_MULTIPLIER;
	}
}
