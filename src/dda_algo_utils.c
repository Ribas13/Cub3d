/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:29:44 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/20 22:30:07 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	calc_h(int p_x, int p_y, int r_x, int r_y)
{
	int	abs_x;
	int	abs_y;

	if (r_x < 0)
		r_x = 0;
	else if (r_x > (int)ft_data()->map->cols * TILE_SIZE)
		r_x = ft_data()->map->cols * TILE_SIZE;
	if (r_y < 0)
		r_y = 0;
	else if (r_y > (int)ft_data()->map->rows * TILE_SIZE)
		r_y = ft_data()->map->rows * TILE_SIZE;
	abs_x = abs(p_x - r_x);
	abs_y = abs(p_y - r_y);
	return (sqrt((abs_x * abs_x) + (abs_y * abs_y)));
}

float	set_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
