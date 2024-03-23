/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 15:46:44 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_mambo(t_ray *ray)
{
	ray->texture_x_offset = 0;
	ray->cam_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->start_draw = 0;
	ray->end_draw = 0;
	ray->line_height = 0;
	ray->wall_orientation = '\0';
}

void	ray_properties(t_ray *ray, t_player *player, int screen_slice)
{
	//init value to 0
	init_mambo(ray);
	ray->cam_x = 2 * screen_slice / (double)SCREEN_WIDTH - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->cam_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->cam_x;
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

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

t_tiles_img	*get_texture(char wall_orientation)
{
	if (wall_orientation == 'N')
		return (ft_data()->tiles->north);
	else if (wall_orientation == 'E')
		return (ft_data()->tiles->east);
	else if (wall_orientation == 'S')
		return (ft_data()->tiles->south);
	else if (wall_orientation == 'W')
		return (ft_data()->tiles->west);
	return (NULL);
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
		textures_updates(ray, ft_data(),
			get_texture(ray->wall_orientation), screen_slice);
		screen_slice++;
	}
	return (0);
}
