/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 21:49:31 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/22 21:49:31 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	set_ray_orientation(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x == -1)
			return ('E');
		else
			return ('W');
	}
	else
	{
		if (ray->step_y == -1)
			return ('N');
		else
			return ('S');
	}
}

int	get_texture_color(t_tiles_img *texture, int texture_x_offset, int texture_y)
{
	int	color;
	int	*arr;

	if (!texture)
		printf("Error\n");
	if (!texture->addr)
		printf("Error 2\n");
	arr = (int *)texture->addr;
	color = arr[texture_y * texture->width + texture_x_offset];
	return (color);
}

void	textures_updates(t_ray *ray, t_data *data, t_tiles_img *texture, int screen_slice)
{	
	int	y;
	int	color;

	(void) data;
	texture->x = (int)(ray->wall_x * TILE_SIZE);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		texture->x = TILE_SIZE - texture->x - 1;
	texture->step = 1.0 * TILE_SIZE / ray->line_height;
	texture->pos = (ray->start_draw - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * texture->step;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		/* printf("ceiling color: %d\n", ft_data()->ceiling);
		printf("floor color: %d\n", ft_data()->floor); */
		while (y < ray->start_draw)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_slice, y, ft_data()->ceiling);
			y++;
		}
		while (y <= ray->end_draw)
		{
			texture->y = (int)texture->pos & (TILE_SIZE - 1);
			texture->pos += texture->step;
			color = get_texture_color(texture, texture->x, texture->y);
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_slice, y, color);
			y++;
		}
		while (y < SCREEN_HEIGHT)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_slice, y, ft_data()->floor);
			y++;
		}
		y++;
	}
}