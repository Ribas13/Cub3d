/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:22:42 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/11 13:25:30 by diosanto         ###   ########.fr       */
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
			errors("Error allocating map1");
		i++;
	}
	data->map->cols = ft_strlen(data->map->map[0]);
	close(map_fd);
}

void	save_map(char *map)
{
	get_nbr_rows(map, ft_data());
	ft_data()->map->map = malloc((ft_data()->map->rows + 1) * sizeof(char *));
	if (!ft_data()->map->map)
		errors("Error allocating map");
	get_lines(map, ft_data());
}

//loop to look at each line
	//Requirements:
	//Must be surrounded by '1', so first and last lines must be all '1'
	//Beggining and end of each line in between must also be a '1'
	//Must contain player spawn location(N, S, W, E)
	//First, save the map to an array of strings
bool	map_check(char *map)
{
	save_map(map);
	//printf map array
	for (int i = 0; ft_data()->map->map[i]; i++)
	{
		printf("%s\n", ft_data()->map->map[i]);
	}
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

/* Check for invalid number of args
Check for invalid extension */
void	valid_map(int ac, char **av)
{
	if (ac != 2)
		errors("Invalid number of arguments");
	else if (!valid_extension(av[1]))
		errors("File must be '.cub'");
	map_check(av[1]);
}
