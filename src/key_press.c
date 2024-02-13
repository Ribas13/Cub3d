/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/13 19:50:01 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	quit_game(void)
{
	clean_all(ft_data());
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	on_press(int key, t_data *data)
{
	if (key == ESC)
		quit_game();
	else if (key == W || key == UP)
		update_player_pos(false, -1);
	else if (key == A || key == LEFT)
		update_player_pos(true, -1);
	else if (key == S || key == DOWN)
		update_player_pos(false, 1);
	else if (key == D || key == RIGHT)
		update_player_pos(true, 1);
	return (EXIT_SUCCESS);
}

void	key_press1(t_data *data)
{
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, data);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, data);
	mlx_loop(data->mlx_ptr);
}
