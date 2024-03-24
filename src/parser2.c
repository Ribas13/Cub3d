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
	if (!tmp[0] || !tmp[1] || !tmp[2])
		errors2("RGB values must have 3 components", tmp);
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	free_array(tmp);
	return (hex);
}

int	get_sidepath(char **tmp, char *str, char *path, t_data *data)
{
	bool	has_error;

	has_error = true;
	if (!str || !path)
		errors2("Something is missing in the map", tmp);
	if (str[0] && path[0])
	{
		if (ft_strcmp(str, "NO") == 0)
		{
			has_error = false;
			data->path_north = ft_strdup(path);
		}
		else if (ft_strcmp(str, "SO") == 0)
		{
			has_error = false;
			data->path_south = ft_strdup(path);
		}
		if (has_error == true)
			has_error = get_sidepath2(tmp, str, path, data);
	}
	if (has_error)
		errors2("Wrong syntax in the texture path", tmp);
	return (1);
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
