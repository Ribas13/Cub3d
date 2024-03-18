/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:05:36 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/18 16:42:45 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//utils
char	**allocate_tmp(t_data *data)
{
	return (ft_calloc(data->map->rows, sizeof(char *)));
}

int	if_map(char str)
{
	if (str == '1' || str == '0'
		|| str == 'N' || str == 'S' || str == 'W' || str == 'E')
		return (1);
	return (0);
}

int	ifnot_map(char str)
{
	if (str == ' ' && str == '1' && str == '0'
		&& str == 'N' && str == 'S' && str == 'W' && str == 'E'
		&& str == '\n')
		return (1);
	return (0);
}

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
