/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/23 15:17:56 by diosanto         ###   ########.fr       */
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
