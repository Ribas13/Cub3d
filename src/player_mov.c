/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/06 16:10:54 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* @brief Moves the player forward based on the player direction */
void	move_forward(void)
{
	ft_data()->player->f_x += ft_data()->player->delta_x;
	ft_data()->player->f_y += ft_data()->player->delta_y;
	ft_data()->player->pos.x = (int)ft_data()->player->f_x;
	ft_data()->player->pos.y = (int)ft_data()->player->f_y;
}

/* @brief Moves the player back based on the player direction */
void	move_back(void)
{
	ft_data()->player->f_x -= ft_data()->player->delta_x;
	ft_data()->player->f_y -= ft_data()->player->delta_y;
	ft_data()->player->pos.x = (int)ft_data()->player->f_x;
	ft_data()->player->pos.y = (int)ft_data()->player->f_y;
}

/* @brief Not used during normal program execution */
void	put_player(void)
{
	size_t	i;
	size_t	j;

	i = -4;
	while (i < 4)
	{
		j = -4;
		while (j < 4)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
				ft_data()->player->pos.x + j, ft_data()->player->pos.y + i,
				0xFF0000);
			j++;
		}
		i++;
	}
}
