/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:22:42 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/11 12:10:56 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	errors(char *error_msg)
{
	printf("%s\n", error_msg);
	exit(1);
}

char	**save_map(char *map)
{
	char	**map_array;
	char	*line;
	int		i;
	int		map_fd;

	i = 0;
	map_fd = open(map, O_RDONLY);
	if (map_fd < 0)
		errors("Error opening file");
	map_array = malloc(sizeof(char *) * 100);
	while (get_next_line(map_fd, &line) > 0)
	{
		map_array[i] = ft_strdup(line);
		i++;
	}
	return (map_array);
}

//loop to look at each line
	//Requirements:
	//Must be surrounded by '1', so first and last lines must be all '1'
	//Beggining and end of each line in between must also be a '1'
	//Must contain player spawn location(N, S, W, E)
	//First, save the map to an array of strings
bool	map_check(char *map)
{
	int		map_file;
	char	*line;
	int		i;
	int		j;

	ft_data()->map->map = save_map(map);
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
	//save_map(av);
}
