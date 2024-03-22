/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:05:36 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/22 19:19:08 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//utils
char	**allocate_tmp(t_data *data)
{
	return (ft_calloc(data->map->rows, sizeof(char *)));
}

int	if_map(char str)
{
	if (str == '1' || str == '0'
		|| str == 'N' || str == 'S' || str == 'W' || str == 'E')
		return (1);
	return (0);
}

int	ifnot_map(char str)
{
	if (str == ' ' && str == '1' && str == '0'
		&& str == 'N' && str == 'S' && str == 'W' && str == 'E'
		&& str == '\n')
		return (1);
	return (0);
}

