/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 16:00:55 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(void)
{
	ft_data()->player->pos.x -= ft_data()->player->plane_x * 0.05;
	ft_data()->player->pos.y -= ft_data()->player->plane_y * 0.05;
}

void	move_right(void)
{
	ft_data()->player->pos.x += ft_data()->player->plane_x * 0.05;
	ft_data()->player->pos.y += ft_data()->player->plane_y * 0.05;
}

/* @brief Moves the player right based on the player direction */
void	move_back(void)
{
	ft_data()->player->pos.x -= ft_data()->player->dir_x * 0.05;
	ft_data()->player->pos.y -= ft_data()->player->dir_y * 0.05;
}

/* @brief Moves the player left based on the player direction */
void	move_forward(void)
{
	ft_data()->player->pos.x += ft_data()->player->dir_x * 0.05;
	ft_data()->player->pos.y += ft_data()->player->dir_y * 0.05;
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
