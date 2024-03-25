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

int	array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

unsigned int	rgb_to_hex(char *str, char **tmp)
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;
	char			**tmp2;

	if (rgb_verify(str) == 1)
		errors2("Invalid RGB syntax", tmp);
	tmp2 = ft_split(str, ',');
	if (!tmp2[0] || !tmp2[1] || !tmp2[2] || array_size(tmp2) > 3)
	{
		free_array(tmp2);
		errors2("RGB values must have 3 components", tmp);
	}
	r = ft_atoi(tmp2[0]);
	g = ft_atoi(tmp2[1]);
	b = ft_atoi(tmp2[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_array(tmp2);
		errors2("RGB values must be between 0 and 255", tmp);
	}
	hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	free_array(tmp2);
	return (hex);
}

int	get_sidepath(char **tmp, char *str, char *path, t_data *data)
{
	bool	has_error;

	has_error = true;
	if (!str || !path || array_size(tmp) > 2)
		errors2("Invalid texture/color syntax", tmp);
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
		errors2("Invalid texture syntax", tmp);
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
	map_texture_error_check(data, i, flag, tmp);
	get_real_map(data, i);
	get_max_player_pos(data);
	return (EXIT_SUCCESS);
}
