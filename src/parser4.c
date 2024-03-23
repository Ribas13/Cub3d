/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:05:36 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 11:56:35 by micarrel         ###   ########.fr       */
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
