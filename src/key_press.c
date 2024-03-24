/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 14:11:52 by micarrel         ###   ########.fr       */
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
	else if (key == LEFT)
		ft_data()->keys->left = true;
	else if (key == RIGHT)
		ft_data()->keys->right = true;
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
	else if (key == LEFT)
		ft_data()->keys->left = false;
	else if (key == RIGHT)
		ft_data()->keys->right = false;
	return (0);
}
int check_wall(int key)
{
	if (key == W)
	{
		if (ft_data()->map->map[(int)(ft_data()->player->pos.y
				+ ft_data()->player->dir_y * 0.1)]
				[(int)(ft_data()->player->pos.x
				+ ft_data()->player->dir_x * 0.1)] == '1')
			return (0);
	}
	if (key == S)
	{
		if (ft_data()->map->map[(int)(ft_data()->player->pos.y
				- ft_data()->player->dir_y * 0.1)]
				[(int)(ft_data()->player->pos.x
				- ft_data()->player->dir_x * 0.1)] == '1')
			return (0);
	}
	return (1);
}

/* @brief Handle player movement based on the keys pressed(aux function) */
void	hooks_2(void)
{
	if (ft_data()->keys->left == true)
		rotate(-1);
	if (ft_data()->keys->right == true)
		rotate(1);
}

/* @brief Handle player movement based on the keys pressed */
void	hooks(void)
{
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
	if (ft_data()->keys->a == true)
	{
		if (ft_data()->map->map[(int)(ft_data()->player->pos.y
				+ ft_data()->player->dir_x * 0.1)]
				[(int)(ft_data()->player->pos.x
				- ft_data()->player->dir_y * 0.1)] == '0')
			move_left();
	}
	if (ft_data()->keys->d == true)
	{
		if (ft_data()->map->map[(int)(ft_data()->player->pos.y
				- ft_data()->player->dir_x * 0.1)]
				[(int)(ft_data()->player->pos.x
				+ ft_data()->player->dir_y * 0.1)] == '0')
			move_right();
	}
	hooks_2();
}

/* @brief Setup all the hooks for the game
	@param *data Game data pointer */
void	key_press1(t_data *data)
{
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(ft_data()->mlx_ptr, ft_data()->win_ptr,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop_hook(data->mlx_ptr, test1, NULL);
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, NULL);
	mlx_hook(data->win_ptr, KEYRELEASE_EVENT, (1L << 1), on_release, NULL);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, NULL);
	mlx_hook(data->win_ptr, MOTION_NOTIFY_EVENT, (1L << 6), mouse_move, NULL);
	mlx_loop(data->mlx_ptr);
}
