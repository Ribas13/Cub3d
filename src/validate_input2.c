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

void	check_invalid_chars(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (!ft_strchr(ALLOWED_CHARS, data->map->map[i][j]))
				errors("Invalid character in map 😭");
			j++;
		}
		i++;
	}
}

void	check_borders(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (i == 0 || i == (data->map->rows - 1))
			{
				if (data->map->map[i][j] != '1')
					errors("Map must be surrounded by '1' 😭");
			}
			else if (j == 0 || j == (data->map->cols - 1))
			{
				if (data->map->map[i][j] != '1')
					errors("Map must be surrounded by '1' 😭");
			}
			j++;
		}
		i++;
	}
}

void	check_player(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	player;

	i = 0;
	player = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (ft_strchr(PLAYER_CHARS, data->map->map[i][j]))
			{
				if (player == 1)
					errors("Map must contain only one player 😭");
				player++;
			}
			j++;
		}
		i++;
	}
	if (player == 0)
		errors("Map must contain a player 😭");
}

bool	map_check(char *map)
{
	save_map(map);
	return (true);
}

bool	valid_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file) - 4;
	if (ft_strncmp(".cub", &file[i], 4) == 0)
		return (true);
	return (false);
}
