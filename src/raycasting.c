/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/22 20:38:31 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ray_properties(t_ray *ray, t_player *player, int screen_slice)
{
	//init value to 0
	ray->cam_x = 2 * screen_slice / (double)SCREEN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
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
		else if (map->map[ray->map_y][ray->map_x] > '0')
			hit = true;
	}
}

void	init_player_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
}

int	raycasting(void)
{
	t_ray		ray;
	int			screen_slice;

	screen_slice = 0;
	init_player_north(ft_data()->player);
	ray = ft_data()->ray;
	while (screen_slice < SCREEN_WIDTH)
	{
		//initialize ray
			//ray_properties
		ray_properties(&ray, ft_data()->player, screen_slice);
		//setup algo
			//perform algo
		setup_algo(&ray, ft_data()->player);
		dda_algo(&ray, ft_data()->map);
		//get_distance
			//setup textures
	}
	return (0);
}
