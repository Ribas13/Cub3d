/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 14:01:32 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_line_height(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(SCREEN_HEIGHT / ray->wall_dist);
	ray->start_draw = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->start_draw < 0)
		ray->start_draw = 0;
	ray->end_draw = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->end_draw >= SCREEN_HEIGHT)
		ray->end_draw = SCREEN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos.x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	setup_algo(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos.x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos.x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos.y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos.y) * ray->deltadist_y;
	}
}

void	dda_algo(t_ray *ray, t_map *map)
{
	bool	hit;

	hit = false;
	while (hit == false)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > map->rows - 0.25
			|| ray->map_x > map->cols - 1.25)
			break ;
		else if (map->map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
}

int	raycasting(void)
{
	t_ray		*ray;
	int			screen_slice;

	screen_slice = 0;
	ray = ft_data()->ray;
	while (screen_slice < SCREEN_WIDTH)
	{
		ray_properties(ray, ft_data()->player, screen_slice);
		setup_algo(ray, ft_data()->player);
		dda_algo(ray, ft_data()->map);
		get_line_height(ray, ft_data()->player);
		ray->wall_orientation = set_ray_orientation(ray);
		textures_updates(ray, get_texture(ray->wall_orientation), screen_slice);
		screen_slice++;
	}
	return (0);
}
