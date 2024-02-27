/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/27 14:28:36 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	quit_game(void)
{
	clean_all(ft_data());
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

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

int	on_press(int key)
{
	ft_data()->player->delta_x = cos(ft_data()->player->dir) * 8;
	ft_data()->player->delta_y = sin(ft_data()->player->dir) * 8;
	if (key == ESC)
	{
		ft_data()->keys->esc = true;
		quit_game();
	}
	else if (key == W)
	{
		if (check_wall(key))
		{
			ft_data()->player->pos.x += ft_data()->player->delta_x;
			ft_data()->player->pos.y += ft_data()->player->delta_y;
		}
	}
	else if (key == A)
	{
		ft_data()->player->dir -= PI / 64;
		if (ft_data()->player->dir < 0)
			ft_data()->player->dir += 2 * PI;
	}
	else if (key == S)
	{
		if (check_wall(key))
		{
			ft_data()->player->pos.x -= ft_data()->player->delta_x;
			ft_data()->player->pos.y -= ft_data()->player->delta_y;
		}
	}
	else if (key == D)
	{
		ft_data()->player->dir += PI / 64;
		if (ft_data()->player->dir > 2 * PI)
			ft_data()->player->dir -= 2 * PI;
	}
	cast_rays();
	//render_tiles();
	//draw_player_rays();
	return (1);
}

void	key_press1(t_data *data)
{
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, data);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, data);
	mlx_loop(data->mlx_ptr);
}
