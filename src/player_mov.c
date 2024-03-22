/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/22 22:53:10 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* @brief Moves the player right based on the player direction */
void	move_right(void)
{
	// ft_data()->player->f_x -= ft_data()->player->delta_y;
	// ft_data()->player->f_y += ft_data()->player->delta_x;
	// ft_data()->player->pos.x = (int)ft_data()->player->f_x;
	// ft_data()->player->pos.y = (int)ft_data()->player->f_y;
	if (ft_data()->player->pos.y + 0.05 < ft_data()->player->y_max)
		ft_data()->player->pos.y += 0.05;
}

/* @brief Moves the player left based on the player direction */
void	move_left(void)
{
	// ft_data()->player->f_x -= ft_data()->player->delta_y;
	// ft_data()->player->f_y += ft_data()->player->delta_x;
	// ft_data()->player->pos.x = (int)ft_data()->player->f_x;
	// ft_data()->player->pos.y = (int)ft_data()->player->f_y;
	if (ft_data()->player->pos.y - 0.05 > 0)
		ft_data()->player->pos.y -= 0.05;
}

/* @brief Moves the player forward based on the player direction */
void	move_forward(void)
{
	// ft_data()->player->f_x += ft_data()->player->delta_x;
	// ft_data()->player->f_y += ft_data()->player->delta_y;
	// ft_data()->player->pos.x = (int)ft_data()->player->f_x;
	// ft_data()->player->pos.y = (int)ft_data()->player->f_y;
	if (ft_data()->player->pos.x + 0.05 < ft_data()->player->x_max)
		ft_data()->player->pos.x += 0.05;
	printf("f_x: %f\n", ft_data()->player->pos.x);
}

/* @brief Moves the player back based on the player direction */
void	move_back(void)
{
	// ft_data()->player->f_x -= ft_data()->player->delta_x;
	// ft_data()->player->f_y -= ft_data()->player->delta_y;
	// ft_data()->player->pos.x = (int)ft_data()->player->f_x;
	// ft_data()->player->pos.y = (int)ft_data()->player->f_y;
	if (ft_data()->player->pos.x - 0.05 > 0)
		ft_data()->player->pos.x -= 0.05;
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
