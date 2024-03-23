/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 00:03:12 by diosanto         ###   ########.fr       */
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

/* void	rotate_right(void)
{
	double		tmp_x;
	double		rotspd;

	rotspd = ROTSPD * 1;
	tmp_x = ft_data()->player->dir_x;
	ft_data()->player->dir_x = ft_data()->player->dir_x * cos(rotspd)
		- ft_data()->player->dir_y * sin(rotspd);
	ft_data()->player->dir_y = tmp_x * sin(rotspd) + ft_data()->player->dir_y
		* cos(rotspd);
	tmp_x = ft_data()->player->plane_x;
	ft_data()->player->plane_x = ft_data()->player->plane_x * cos(rotspd)
		- ft_data()->player->plane_y * sin(rotspd);
	ft_data()->player->plane_y = tmp_x * sin(rotspd) + ft_data()->player->plane_y * cos(rotspd);
	return ;
} */

//rotspeed = rotatedir * rotspeed ------> -1
void	rotate(int rotspd)
{
	double		tmp_x;

	rotspd = ROTSPD * rotspd;
	tmp_x = ft_data()->player->dir_x;
	ft_data()->player->dir_x = ft_data()->player->dir_x * cos(rotspd)
		- ft_data()->player->dir_y * sin(rotspd);
	ft_data()->player->dir_y = tmp_x * sin(rotspd) + ft_data()->player->dir_y
		* cos(rotspd);
	tmp_x = ft_data()->player->plane_x;
	ft_data()->player->plane_x = ft_data()->player->plane_x * cos(rotspd)
		- ft_data()->player->plane_y * sin(rotspd);
	ft_data()->player->plane_y = tmp_x * sin(rotspd) + ft_data()->player->plane_y * cos(rotspd);
	return ;
}

/* @brief Handle player movement based on the keys pressed(aux function) */
void	hooks_2(void)
{
	if (ft_data()->keys->a == true)
	{
		// ft_data()->player->dir -= PI / 64;
		// if (ft_data()->player->dir < 0)
		// 	ft_data()->player->dir += 2 * PI;
		//move_left();
		rotate(-1);
	}
	if (ft_data()->keys->d == true)
	{
		// ft_data()->player->dir += PI / 64;
		// if (ft_data()->player->dir > 2 * PI)
		// 	ft_data()->player->dir -= 2 * PI;
		//move_right();
		rotate(1);
	}
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
	hooks_2();
}

/* @brief Setup all the hooks for the game
	@param *data Game data pointer */
void	key_press1(t_data *data)
{
	// ft_data()->player->f_x = ft_data()->player->pos.x;
	// ft_data()->player->f_y = ft_data()->player->pos.y;
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(ft_data()->mlx_ptr, ft_data()->win_ptr,
		SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop_hook(data->mlx_ptr, test1, NULL);
	//mlx_loop_hook(data->mlx_ptr, render_tiles, NULL);
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, NULL);
	mlx_hook(data->win_ptr, KEYRELEASE_EVENT, (1L << 1), on_release, NULL);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, NULL);
	mlx_hook(data->win_ptr, MOTION_NOTIFY_EVENT, (1L << 6), mouse_move, NULL);
	mlx_loop(data->mlx_ptr);
}
