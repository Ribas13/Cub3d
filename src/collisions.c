/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:52 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 15:07:18 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_valid_pos(t_data *data, double x, double y)
{
	if (data->map->map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

void	valid_move(t_data *data, double n_x, double n_y)
{
	double	x_margin;
	double	y_margin;

	x_margin = 0;
	y_margin = 0;
	if (ft_data()->player->pos.x < n_x)
		x_margin = 0.1;
	else if (ft_data()->player->pos.x > n_x)
		x_margin = -0.1;
	if (ft_data()->player->pos.y < n_y)
		y_margin = 0.1;
	else if (ft_data()->player->pos.y > n_y)
		y_margin = -0.1;
	if (is_valid_pos(data, n_x + x_margin, data->player->pos.y))
		data->player->pos.x = n_x;
	if (is_valid_pos(data, data->player->pos.x, n_y + y_margin))
		data->player->pos.y = n_y;
}
