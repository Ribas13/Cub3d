/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/16 15:14:45 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	quit_game(void)
{
	clean_all(ft_data());
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void		rotate_player(int dir)
{
	ft_data()->player->dir += (M_PI / 180) * dir;
}

int	on_press(int key)
{
	if (key == ESC)
		quit_game();
	else if (key == W || key == UP)
		update_player_pos(false, -1);
	else if (key == A)
		update_player_pos(true, -1);
	else if (key == S || key == DOWN)
		update_player_pos(false, 1);
	else if (key == D)
		update_player_pos(true, 1);
	else if (key == RIGHT)
		rotate_player(1);
	else if (key == LEFT)
		rotate_player(-1);
	else
		return (EXIT_FAILURE);
	put_player();
	cast_rays();
	return (EXIT_SUCCESS);
}

void	key_press1(t_data *data)
{
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, data);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, data);
	mlx_loop(data->mlx_ptr);
}
