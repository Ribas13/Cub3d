/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:18:46 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/18 16:18:46 by micarrel         ###   ########.fr       */
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

unsigned int	rgb_to_hex(char *str, char **tmp)
{
	int				r;
	int				g;
	int				b;
	int				i;
	unsigned int	hex;

	i = 0;
	while (str[i]) 
	{
		if (!ft_isdigit(str[i]) && str[i] != ',') 
		{
			free_array(tmp);
			errors("Invalid characters in the string");
		}
		i++;
	}
	tmp = ft_split(str, ',');
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	free_array(tmp);
	return (hex);
}

int	get_sidepath(char **tmp, char *str, char *path, t_data *data)
{
	if (!str || !path)
	{
		free_array(tmp);
		errors("Something is missing in the map");
	}
	if (str[0] && path[0])
	{
		if (ft_strncmp(str, "NO", 2) == 0)
			data->path_north = ft_strdup(path);
		else if (ft_strncmp(str, "SO", 2) == 0)
			data->path_south = ft_strdup(path);
		else if (ft_strncmp(str, "WE", 2) == 0)
			data->path_west = ft_strdup(path);
		else if (ft_strncmp(str, "EA", 2) == 0)
			data->path_east = ft_strdup(path);
		else if (ft_strncmp(str, "F", 2) == 0)
			data->floor = rgb_to_hex(path, tmp);
		else if (ft_strncmp(str, "C", 2) == 0)
			data->ceiling = rgb_to_hex(path, tmp);
		return (1);
	}
	return (0);
}

void	get_max_player_pos(t_data *data)
{
	double	x_max;
	double	y_max;

	x_max = 0;
	y_max = 0;
	while (data->map->map[(int)y_max])
	{
		if (x_max < ft_strlen(data->map->map[(int)y_max]))
			x_max = ft_strlen(data->map->map[(int)y_max]);
		y_max++;
	}
	data->player->x_max = x_max;
	data->player->y_max = y_max;
}

int	map_texture(t_data *data)
{
	int		i;
	int		flag;
	char	**tmp;

	i = 0;
	flag = 0;
	tmp = NULL;
	while (data->map->map[i])
	{
		tmp = ft_split(data->map->map[i], ' ');
		if (tmp[0] && get_sidepath(tmp, tmp[0], tmp[1], data) == 1)
			flag++;
		else if (flag >= 6)
			break ;
		free_array(tmp);
		i++;
	}
	if (flag < 6)
		errors("Something is missing in the map");
	if (tmp)
		free_array(tmp);
	get_real_map(data, i);
	get_max_player_pos(data);
	return (EXIT_SUCCESS);
}
