/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:05:36 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/18 00:52:07 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_collision(int x, int y)
{
	int	buffer;

	buffer = 15;
	if (ft_data()->map->map[(y - buffer) / TILE_SIZE]
		[(x - buffer) / TILE_SIZE] == '1'
		|| ft_data()->map->map[(y - buffer) / TILE_SIZE]
		[(x + buffer) / TILE_SIZE] == '1'
		|| ft_data()->map->map[(y + buffer) / TILE_SIZE]
		[(x - buffer) / TILE_SIZE] == '1'
		|| ft_data()->map->map[(y + buffer) / TILE_SIZE]
		[(x + buffer) / TILE_SIZE] == '1')
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
		if (ft_data()->map->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
			return (0);
	}
	else if (key == S)
	{
		x = ft_data()->player->pos.x - ft_data()->player->delta_x;
		y = ft_data()->player->pos.y - ft_data()->player->delta_y;
		if (ft_data()->map->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
			return (0);
	}
	return (1);
}
