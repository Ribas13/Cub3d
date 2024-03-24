/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 15:06:35 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(void)
{
	valid_move(ft_data(), ft_data()->player->pos.x
		- ft_data()->player->plane_x * 0.1,
		ft_data()->player->pos.y - ft_data()->player->plane_y * 0.1);
}

void	move_right(void)
{
	valid_move(ft_data(), ft_data()->player->pos.x
		+ ft_data()->player->plane_x * 0.1,
		ft_data()->player->pos.y + ft_data()->player->plane_y * 0.1);
}

/* @brief Moves the player right based on the player direction */
void	move_back(void)
{
	valid_move(ft_data(), ft_data()->player->pos.x
		- ft_data()->player->dir_x * 0.1,
		ft_data()->player->pos.y - ft_data()->player->dir_y * 0.1);
}

/* @brief Moves the player left based on the player direction */
void	move_forward(void)
{
	valid_move(ft_data(), ft_data()->player->pos.x
		+ ft_data()->player->dir_x * 0.1,
		ft_data()->player->pos.y + ft_data()->player->dir_y * 0.1);
}

void	rotate(double rotspd)
{
	double		tmp_x;

	rotspd = ROTSPD * rotspd;
	tmp_x = ft_data()->player->dir_x;
	ft_data()->player->dir_x = ft_data()->player->dir_x * cos(rotspd)
	- ft_data()->player->dir_y * sin(rotspd);
	ft_data()->player->dir_y = tmp_x * sin(rotspd)
	+ ft_data()->player->dir_y * cos(rotspd);
	tmp_x = ft_data()->player->plane_x;
	ft_data()->player->plane_x = ft_data()->player->plane_x
	* cos(rotspd) - ft_data()->player->plane_y * sin(rotspd);
	ft_data()->player->plane_y = tmp_x * sin(rotspd)
	+ ft_data()->player->plane_y * cos(rotspd);
}
