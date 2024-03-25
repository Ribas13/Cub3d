/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validade_input2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:39:34 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/18 00:39:34 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rgb_verify(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
		{
			if (str[i + 1] == ',')
				return (1);
			if (str[i + 1] == '\0')
				return (1);
		}
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (1);
		i++;
	}
	return (0);
}

int	adjust_count(char **tmp, int count)
{
	if (tmp[count] && ft_strchr(tmp[count], '1') == NULL)
		count--;
	return (count);
}

bool	valid_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(".cub", &file[i], 4) == 0)
		return (true);
	return (false);
}

int	validate_map(void)
{
	int	i;
	int	j;

	i = 0;
	while (ft_data()->map->map[i])
	{
		j = 0;
		while (ft_data()->map->map[i][j])
		{
			if (is_closed(i, j) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	map_verify(t_data *data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	if (validate_map() == 1)
		return (1);
	get_columns_lines(data, data->map->map);
	if (data->map->cols < 3 || data->map->rows < 3)
		return (1);
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
			if (strchr("NSWE", data->map->map[i][j++]))
				count++;
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}
