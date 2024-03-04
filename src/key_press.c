/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:39:12 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/04 19:16:09 by diosanto         ###   ########.fr       */
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

int	mouse_position(void)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(ft_data()->mlx_ptr, ft_data()->win_ptr, &x, &y);
	if (x > SCREEN_WIDTH)
		x = SCREEN_WIDTH;
	else if (x < 0)
		x = 0;
	if (x < SCREEN_WIDTH / 2)
	{
		mlx_mouse_move(ft_data()->mlx_ptr, ft_data()->win_ptr,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		return (-1);
	}
	else if (x > SCREEN_WIDTH / 2)
	{
		mlx_mouse_move(ft_data()->mlx_ptr,
			ft_data()->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		return (1);
	}
	return (0);
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
		ft_data()->keys->w = true;
	else if (key == A)
		ft_data()->keys->a = true;
	else if (key == S)
		ft_data()->keys->s = true;
	else if (key == D)
		ft_data()->keys->d = true;
	return (0);
}

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
	//ft_data()->player->delta_x = 0;
	//ft_data()->player->delta_y = 0;
	return (0);
}

void	hooks_2(void)
{
	if (ft_data()->keys->a == true)
	{
		ft_data()->player->dir -= PI / 64;
		if (ft_data()->player->dir < 0)
			ft_data()->player->dir += 2 * PI;
	}
	if (ft_data()->keys->d == true)
	{
		ft_data()->player->dir += PI / 64;
		if (ft_data()->player->dir > 2 * PI)
			ft_data()->player->dir -= 2 * PI;
	}
}

void	hooks(void)
{
	if (ft_data()->keys->w == true)
	{
		if (check_wall(W))
		{
			ft_data()->player->pos.x += ft_data()->player->delta_x;
			ft_data()->player->pos.y += ft_data()->player->delta_y;
		}
	}
	if (ft_data()->keys->s == true)
	{
		if (check_wall(S))
		{
			ft_data()->player->pos.x -= ft_data()->player->delta_x;
			ft_data()->player->pos.y -= ft_data()->player->delta_y;
		}
	}
	hooks_2();
}

int	mouse_move(void)
{
	ft_data()->keys->mouse = mouse_position();
	if (ft_data()->keys->mouse == -1)
		ft_data()->player->dir -= PI / 64;
	else if (ft_data()->keys->mouse == 1)
		ft_data()->player->dir += PI / 64;
	//mouse_position();
	return (0);
}

void	key_press1(t_data *data)
{
	mlx_mouse_hide(data->mlx_ptr, data->win_ptr);
	mlx_mouse_move(ft_data()->mlx_ptr, ft_data()->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop_hook(data->mlx_ptr, cast_rays, NULL);
	mlx_hook(data->win_ptr, KEYPRESS_EVENT, (1L << 0), on_press, NULL);
	mlx_hook(data->win_ptr, KEYRELEASE_EVENT, (1L << 1), on_release, NULL);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY_EVENT, (1L << 17), quit_game, NULL);
	//mlx_hook to put mouse in the middle of the screen
	mlx_hook(data->win_ptr, MOTION_NOTIFY_EVENT, (1L << 6), mouse_move, NULL);
	//mlx_mouse_move(data->mlx_ptr, data->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_loop(data->mlx_ptr);
}
