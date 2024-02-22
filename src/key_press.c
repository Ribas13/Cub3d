/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/22 18:43:16 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	quit_game(void)
{
	clean_all(ft_data());
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	on_press(int key)
{
	if (key == ESC)
		quit_game();
	else if (key == W)
	{
		printf("INSIDE W\n");
		printf("Angle: %f\n", ft_data()->player->dir);
		printf("X: %i and Y: %i\n", ft_data()->player->pos.x, ft_data()->player->pos.y);
		ft_data()->player->pos.x += ft_data()->player->delta_x;
		ft_data()->player->pos.y += ft_data()->player->delta_y;
	}
	else if (key == A)
	{
		ft_data()->player->dir -= 0.1;
		printf("INSIDE A\n");
		printf("Angle: %f\n", ft_data()->player->dir);
		printf("X: %i and Y: %i\n", ft_data()->player->pos.x, ft_data()->player->pos.y);
		if (ft_data()->player->dir < 0)
			ft_data()->player->dir += 2 * PI;
		ft_data()->player->delta_x = cos(ft_data()->player->dir) * 5;
		ft_data()->player->delta_y = sin(ft_data()->player->dir) * 5;
	}
	else if (key == S)
	{
		printf("INSIDE S\n");
		printf("Angle: %f\n", ft_data()->player->dir);
		printf("X: %i and Y: %i\n", ft_data()->player->pos.x, ft_data()->player->pos.y);
		ft_data()->player->pos.x += -1 * (ft_data()->player->delta_x);
		ft_data()->player->pos.y += -1 * (ft_data()->player->delta_y);
	}
	else if (key == D)
	{
		printf("INSIDE D\n");
		printf("Angle: %f\n", ft_data()->player->dir);
		printf("X: %i and Y: %i\n", ft_data()->player->pos.x, ft_data()->player->pos.y);
		ft_data()->player->dir += 0.1;
		if (ft_data()->player->dir > 2 * PI)
			ft_data()->player->dir -= 2 * PI;
		ft_data()->player->delta_x = cos(ft_data()->player->dir) * 5;
		ft_data()->player->delta_y = sin(ft_data()->player->dir) * 5;
	}
	render_tiles();
	return (1);
}

void	key_press1(t_data *data)
{
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, data);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, data);
	mlx_loop(data->mlx_ptr);
}
