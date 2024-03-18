/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:36:02 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/18 00:50:45 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	ft_emptystr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' )
			return (1);
		i++;
	}
	return (0);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

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

int	empty_line(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0'
			|| str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (0);
	return (1);
}

bool	check_map(t_data *data)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 0;
	flag = 0;
	while (data->map->map[i])
	{
		j = 0;
		if (ft_strlen(data->map->map[i]) == 0 && flag == 0)
			flag = 1;
		while (data->map->map[i][j])
		{
			if ((data->map->map[i][j] == '0' || data->map->map[i][j] == '1' || data->map->map[i][j] == 'N' || data->map->map[i][j] == 'S' || data->map->map[i][j] == 'W' || data->map->map[i][j] == 'E') && flag == 1)
				errors("Empty line in map");
			if (data->map->map[i][j] != '1' && data->map->map[i][j] != ' ')
				if (data->map->map[i][j] != '0' && data->map->map[i][j] != '1' && data->map->map[i][j] != 'N' && data->map->map[i][j] != 'S' && data->map->map[i][j] != 'W' && data->map->map[i][j] != 'E' && data->map->map[i][j] != '\n')
					errors("Invalid character in map");
			j++;
		}
		i++;
	}
	if (validate_map() == 1)
		errors("Map not closed");
	return (true);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	get_real_map(t_data *data, int i)
{
	int		j;
	char	**tmp;
	int		count;

	j = 0;
	tmp = ft_calloc(data->map->rows, sizeof(char *));
	i++;
	while (data->map->map[i])
	{
		if (ft_emptystr(data->map->map[i]) == 1)
		{
			while (data->map->map[i])
			{
				tmp[j] = ft_strdup(data->map->map[i]);
				j++;
				i++;
			}
			tmp[j] = NULL;
			break ;
		}
		i++;
	}
	j = 0;
	while (tmp[j])
		j++;
	count = j;
	if (tmp[j] && ft_strchr(tmp[j], '1') == NULL)
		count = j - 1;
	j = 0;
	while (j)
	{
		if (ft_strchr(tmp[j], '1') == NULL)
		{
			count = j - 1;
			break ;
		}
		j--;
	}
	j = 0;
	free_array(data->map->map);
	data->map->map = ft_calloc(count + 1, sizeof(char *));
	while (ft_strlen(tmp[j]) != 0)
	{
		data->map->map[j] = ft_strdup(tmp[j]);
		j++;
	}
	data->map->map[j] = NULL;
	free_array(tmp);
	return (EXIT_SUCCESS);
}

unsigned int	rgb_to_hex(char *str)
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;
	char			**tmp;

	tmp = ft_split(str, ',');
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	hex = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	free_array(tmp);
	return (hex);
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
		if (tmp[0] && ft_strncmp(tmp[0], "NO", 2) == 0 && flag < 7)
		{
			data->path_north = ft_strdup(tmp[1]); 
			flag++;
		}
		else if (tmp[0] && ft_strncmp(tmp[0], "SO", 2) == 0 && flag < 7)
		{
			data->path_south = ft_strdup(tmp[1]); 
			flag++;
		}
		else if (tmp[0] && ft_strncmp(tmp[0], "WE", 2) == 0 && flag < 7)
		{
			data->path_west = ft_strdup(tmp[1]); 
			flag++;
		}
		else if (tmp[0] && ft_strncmp(tmp[0], "EA", 2) == 0 && flag < 7)
		{
			data->path_east = ft_strdup(tmp[1]); 
			flag++;
		}
		else if (tmp[0] && ft_strncmp(tmp[0], "F", 1) == 0 && flag < 7)
		{
			data->floor = rgb_to_hex(tmp[1]); 
			flag++;
		}
		else if (tmp[0] && ft_strncmp(tmp[0], "C", 1) == 0 && flag < 7)
		{
			data->ceiling = rgb_to_hex(tmp[1]); 
			flag++;
		}
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
	return (EXIT_SUCCESS);
}
