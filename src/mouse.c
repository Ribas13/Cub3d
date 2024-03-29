/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:06:09 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 15:13:57 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	mouse_move(void)
{
	ft_data()->keys->mouse = mouse_position();
	if (ft_data()->keys->mouse != 0)
		rotate(ft_data()->keys->mouse);
	return (0);
}
