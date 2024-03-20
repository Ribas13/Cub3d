/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:37:37 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/18 16:37:37 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	count_valid_rows(char **tmp)
{
	int	j;

	j = 0;
	while (tmp[j])
		j++;
	return (j);
}

int	adjust_count(char **tmp, int count)
{
	if (tmp[count] && ft_strchr(tmp[count], '1') == NULL)
		count--;
	return (count);
}

int	find_last_valid_row(char **tmp, int count)
{
	int	j;

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
	return (count);
}

void	copy_tmp_to_map(t_data *data, char **tmp, int count)
{
	int	j;

	j = 0;
	free_array(data->map->map);
	data->map->map = ft_calloc(count + 1, sizeof(char *));
	while (tmp && tmp[j] && ft_strlen(tmp[j]) != 0)
	{
		data->map->map[j] = ft_strdup(tmp[j]);
		j++;
	}
	data->map->map[j] = NULL;
}

void	get_columns_lines(t_data *data, char **tmp)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (tmp[j])
	{
		if (ft_strlen(tmp[j]) > count)
			count = ft_strlen(tmp[j]);
		j++;
	}
	data->map->cols = count;
	data->map->rows = j;
}

int	get_real_map(t_data *data, int i)
{
	int		j;
	char	**tmp;
	int		count;

	j = 0;
	tmp = allocate_tmp(data);
	i++;
	copy_non_empty_strings(data, tmp, &i, &j);
	count = count_valid_rows(tmp);
	count = adjust_count(tmp, count);
	count = find_last_valid_row(tmp, count);
	copy_tmp_to_map(data, tmp, count);
	free_array(tmp);
	

	i = 0;
	while (data->map->map[i])
	{
		printf("%s\n", data->map->map[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
