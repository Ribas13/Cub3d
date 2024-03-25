/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:01:38 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/25 18:03:06 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_closed(int i, int j)
{
	if (ft_data()->map->map[i][j] == '0' \
		|| (ft_data()->map->map[i][j] != '1'
		&& ft_data()->map->map[i][j] != ' '
		&& ft_data()->map->map[i][j] != '\n'))
	{
		if (i == 0 || !ft_data()->map->map[i + 1]
			|| j == 0 || !ft_data()->map->map[i][j + 1])
			return (1);
		if (ft_data()->map->map[i - 1] && ft_data()->map->map[i - 1][j]
			&& ft_data()->map->map[i - 1][j] == ' ')
			return (1);
		if (ft_data()->map->map[i + 1] && ft_data()->map->map[i + 1][j]
			&& ft_data()->map->map[i + 1][j] == ' ')
			return (1);
		if (ft_data()->map->map[i] && ft_data()->map->map[i][j - 1]
			&& ft_data()->map->map[i][j - 1] == ' ')
			return (1);
		if (ft_data()->map->map[i] && ft_data()->map->map[i][j + 1]
			&& ft_data()->map->map[i][j + 1] == ' ')
			return (1);
	}
	return (0);
}

void	map_texture_error_check(t_data *data, int i, int flag, char **tmp)
{
	if ((int)data->map->rows == i)
		errors("Missing map");
	if (flag < 6)
		errors("Something is missing in the map");
	if (tmp)
		free_array(tmp);
}
