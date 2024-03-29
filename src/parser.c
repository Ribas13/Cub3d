/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:36:02 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/25 17:57:35 by diosanto         ###   ########.fr       */
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
	if (ft_strlen(str) == 0)
		return (0);
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
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
	printf("line %zu\n", ft_strlen(str));
	if (ft_strlen(str) == 0)
		return (1);
	if (str[i] == '\0' || str[i] == '\n')
		return (1);
	while (str && str[i])
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

bool	check_map(t_data *data, int i)
{
	size_t	j;
	int		flag;

	flag = 0;
	while (data->map->map[i])
	{
		j = 0;
		if (ft_strlen(data->map->map[i]) == 0 && flag == 0)
			flag = 1;
		while (data->map->map[i][j])
		{
			if (if_map(data->map->map[i][j]) && flag == 1)
				errors("Invalid map");
			else if (!if_map(data->map->map[i][j]))
				errors("Invalid map");
			if (data->map->map[i][j] != '1' && data->map->map[i][j] != ' ')
				if (ifnot_map(data->map->map[i][j]))
					errors("Invalid map");
			j++;
		}
		i++;
	}
	if (validate_map() == 1)
		errors("Map not closed");
	return (true);
}

void	copy_non_empty_strings(t_data *data, char **tmp, int *i, int *j)
{
	while (data->map->map[*i])
	{
		if (ft_emptystr(data->map->map[*i]) == 1)
			break ;
		(*i)++;
	}
	while (data->map->map[*i])
	{
		if (ft_emptystr(data->map->map[*i]) == 1)
		{
			tmp[*j] = ft_strdup(data->map->map[*i]);
			(*j)++;
		}
		else
			break ;
		(*i)++;
	}
	tmp[*j] = NULL;
	check_after(data, i, tmp);
	return ;
}
