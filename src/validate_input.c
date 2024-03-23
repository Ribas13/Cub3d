/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:22:42 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 15:35:55 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	errors(char *error_msg)
{
	printf("%s\n", error_msg);
	clean_all(ft_data());
	exit(1);
}

void	get_nbr_rows(char *map, t_data *data)
{
	char	*temp;
	size_t	rows;
	int		map_fd;

	rows = 0;
	map_fd = open(map, O_RDONLY);
	temp = get_next_line(map_fd);
	while (temp)
	{
		rows++;
		free(temp);
		temp = get_next_line(map_fd);
	}
	if (rows == 0)
		errors("Empty map");
	data->map->rows = rows;
	close(map_fd);
}

void	get_lines(char *map, t_data *data)
{
	size_t	i;
	int		map_fd;

	i = 0;
	map_fd = open(map, O_RDONLY);
	while (i < data->map->rows)
	{
		data->map->map[i++] = get_next_line(map_fd);
	}
	data->map->map[i] = NULL;
	i = 0;
	while (i < (data->map->rows - 1))
	{
		data->map->map[i] = ft_trim_free(data->map->map[i], "\n");
		if (!data->map->map[i])
			errors("Error allocating map");
		i++;
	}
	data->map->cols = ft_strlen(data->map->map[0]);
	close(map_fd);
}

float	get_player_dir(char c)
{
	if (c == 'N')
		init_player_north(ft_data()->player);
	else if (c == 'E')
		init_player_east(ft_data()->player);
	else if (c == 'S')
		init_player_south(ft_data()->player);
	else if (c == 'W')
		init_player_west(ft_data()->player);
	else
		errors("Player direction assignation error");
	return (0);
}

void	get_player_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data->map->map[i])
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (ft_strchr(PLAYER_CHARS, data->map->map[i][j]))
			{
				/* data->player->pos.x = j;
				data->player->pos.y = i;
				data->player->dir = get_player_dir(data->map->map[i][j]);
				data->map->map[i][j] = '0'; */
				data->player->pos.x = j;
				data->player->pos.y = i;
				data->player->dir = get_player_dir(data->map->map[i][j]);
				data->map->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
