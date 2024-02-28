/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/28 23:37:53 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, ft_data()->player->pos.x + j, ft_data()->player->pos.y + i, 0xFF0000);
			j++;
		}
		i++;
	}
}
