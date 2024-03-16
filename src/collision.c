/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:05:36 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/15 20:05:29 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_collision(int x, int y)
{
	int	buffer;

	buffer = 15;
	if (ft_data()->map->map[(y - buffer) / TILE_SIZE]
		[(x - buffer) / TILE_SIZE] == WALL
		|| ft_data()->map->map[(y - buffer) / TILE_SIZE]
		[(x + buffer) / TILE_SIZE] == WALL
		|| ft_data()->map->map[(y + buffer) / TILE_SIZE]
		[(x - buffer) / TILE_SIZE] == WALL
		|| ft_data()->map->map[(y + buffer) / TILE_SIZE]
		[(x + buffer) / TILE_SIZE] == WALL)
		return (0);
	return (1);
}

//Still need to implement sliding
int	check_wall(int key)
{
	int	x;
	int	y;

	if (key == W)
	{
		x = ft_data()->player->pos.x + ft_data()->player->delta_x;
		y = ft_data()->player->pos.y + ft_data()->player->delta_y;
		if (ft_data()->map->map[y / TILE_SIZE][x / TILE_SIZE] == WALL)
			return (0);
	}
	else if (key == S)
	{
		x = ft_data()->player->pos.x - ft_data()->player->delta_x;
		y = ft_data()->player->pos.y - ft_data()->player->delta_y;
		if (ft_data()->map->map[y / TILE_SIZE][x / TILE_SIZE] == WALL)
			return (0);
	}
	return (1);
}
