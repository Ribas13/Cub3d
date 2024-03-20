/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/20 21:47:05 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* @brief Register and save key pressed state */
int	on_press(int key)
{
	if (key == ESC)
	{
		ft_data()->keys->esc = true;
		quit_game();
	}
	else if (key == W)
		ft_data()->keys->w = true;
	else if (key == A)
		ft_data()->keys->a = true;
	else if (key == S)
		ft_data()->keys->s = true;
	else if (key == D)
		ft_data()->keys->d = true;
	return (0);
}

/* @brief Register and save key released state */
int	on_release(int key)
{
	if (key == W)
		ft_data()->keys->w = false;
	else if (key == A)
		ft_data()->keys->a = false;
	else if (key == S)
		ft_data()->keys->s = false;
	else if (key == D)
		ft_data()->keys->d = false;
	return (0);
}

/* @brief Handle player movement based on the keys pressed(aux function) */
void	hooks_2(void)
{
	if (ft_data()->keys->a == true)
	{
		ft_data()->player->dir -= PI / 128;
		if (ft_data()->player->dir < 0)
			ft_data()->player->dir += 2 * PI;
	}
	if (ft_data()->keys->d == true)
	{
		ft_data()->player->dir += PI / 128;
		if (ft_data()->player->dir > 2 * PI)
			ft_data()->player->dir -= 2 * PI;
	}
}

/* @brief Handle player movement based on the keys pressed */
void	hooks(void)
{
	ft_data()->player->delta_x = cos(ft_data()->player->dir) * 4;
	ft_data()->player->delta_y = sin(ft_data()->player->dir) * 4;
	if (ft_data()->keys->w == true)
	{
		if (check_wall(W))
			move_forward();
	}
	if (ft_data()->keys->s == true)
	{
		if (check_wall(S))
			move_back();
	}
	hooks_2();
}

/* @brief Setup all the hooks for the game
	@param *data Game data pointer */
void	key_press1(t_data *data)
{
	ft_data()->player->f_x = ft_data()->player->pos.x;
	ft_data()->player->f_y = ft_data()->player->pos.y;
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(ft_data()->mlx_ptr, ft_data()->win_ptr,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop_hook(data->mlx_ptr, cast_rays, NULL);
	mlx_loop_hook(data->mlx_ptr, render_tiles, NULL);
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, NULL);
	mlx_hook(data->win_ptr, KEYRELEASE_EVENT, (1L << 1), on_release, NULL);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, NULL);
	mlx_hook(data->win_ptr, MOTION_NOTIFY_EVENT, (1L << 6), mouse_move, NULL);
	mlx_loop(data->mlx_ptr);
}
