/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:47:49 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/15 20:02:12 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	draw_ceiling(int screen_x, int screen_y, int wall_start)
{
	while (screen_y < wall_start && screen_y < SCREEN_HEIGHT)
	{
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
			screen_x, screen_y, 0x87CEEB);
		screen_y++;
	}
	return (screen_y);
}

int	draw_floor(int screen_x, int screen_y)
{
	while (screen_y < SCREEN_HEIGHT)
	{
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
			screen_x, screen_y, 0x8B4513);
		screen_y++;
	}
	return (screen_y);
}

void	draw_wall(int wall_start, int wall_end, int screen_x, t_ray ray)
{
	int			screen_y;
	double		y_offset;
	int			texture_y;
	int			color;

	screen_y = 0;
	while (screen_y < SCREEN_HEIGHT)
	{
		screen_y = draw_ceiling(screen_x, screen_y, wall_start);
		while (screen_y >= wall_start && screen_y < wall_end)
		{
			y_offset = (double)(screen_y - wall_start)
				/ (wall_end - wall_start);
			texture_y = (int)(y_offset * ray.texture->height);
			color = get_texture_color(ray.texture,
					ray.texture_x_offset, texture_y);
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
				screen_x, screen_y, color);
			screen_y++;
		}
		screen_y = draw_floor(screen_x, screen_y);
	}
}

void	draw_ray(t_ray ray)
{
	int	wall_start;
	int	wall_end;
	int	screen_x;
	int	screen_x_end;

	wall_start = calculate_start(ray.distance);
	wall_end = calculate_end(ray.distance);
	screen_x = ray.section;
	screen_x_end = ray.section + 10;
	while (screen_x <= screen_x_end)
	{
		draw_wall(wall_start, wall_end, screen_x, ray);
		screen_x++;
	}
}
