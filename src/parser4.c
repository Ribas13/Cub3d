/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:05:36 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/25 17:57:42 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_after(t_data *data, int *i, char **tmp)
{
	while (data->map->map[*i])
	{
		if (*i == (int)data->map->rows - 1 && data->map->map[*i][0] == '\n')
			break ;
		if (ft_strlen(data->map->map[*i]) != 0)
			errors2("Invalid map", tmp);
		(*i)++;
	}
}

bool	get_sidepath2(char **tmp, char *str, char *path, t_data *data)
{
	bool	has_error;

	has_error = true;
	if (ft_strcmp(str, "WE") == 0)
	{
		has_error = false;
		data->path_west = ft_strdup(path);
	}
	else if (ft_strcmp(str, "EA") == 0)
	{
		has_error = false;
		data->path_east = ft_strdup(path);
	}
	else if (ft_strcmp(str, "F") == 0)
	{
		has_error = false;
		data->floor = rgb_to_hex(path, tmp);
	}
	else if (ft_strcmp(str, "C") == 0)
	{
		has_error = false;
		data->ceiling = rgb_to_hex(path, tmp);
	}
	return (has_error);
}

//utils
char	**allocate_tmp(t_data *data)
{
	return (ft_calloc(data->map->rows, sizeof(char *)));
}

int	if_map(char str)
{
	if (str == '1' || str == '0'
		|| str == 'N' || str == 'S' || str == 'W' || str == 'E'
		|| str == ' ' || str == '\n')
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
