/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:22:42 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/10 20:53:04 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	errors(char *error_msg)
{
	printf("%s\n", error_msg);
	exit(1);
}

/* rules:
1. first and last letters must be '1'
2. Can only contain "01NSWE"
3. Once player has been found, cannot be found again */
void	check_middle_lines(char *line, int i)
{
	if (line[0] != '1' || line[ft_strlen(line)] != '1')
		errors("Map must be enclosed by walls ('1')");
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!ft_strchr(ALLOWED_CHARS, line[i]))
			errors("Map can only contain 0 1 N S W E characters");
		if (ft_strchr(PLAYER_CHARS, line[i]) && ft_data()->map->has_player)
			errors("Map can only contain one player spawn location");
		i++;
	}
}

void	check_line(char *line, int i, int j, bool last_line)
{
	if (i == 0)
	{
		while (line[j] != '\0' && line[j] != '\n')
			if (line[j] != '1')
				errors("First line must be all '1'");
	}
	else if (last_line == true)
	{
		while (line[j] != '\0' && line[j] != '\n')
			if (line[j] != '1')
				errors("Last line must be all '1'");
	}
	else
		check_middle_lines(line, j);
}

//loop to look at each line
	//Requirements:
	//Must be surrounded by '1', so first and last lines must be all '1'
	//Beggining and end of each line in between must also be a '1'
	//Must contain player spawn location(N, S, W, E)
bool	map_check(char *map)
{
	int		map_file;
	char	*line;
	int		i;
	int		j;

	map_file = open(map, O_RDONLY);
	if (!map_file)
		errors("Can't open map file");
	i = 0;
	ft_data()->map->has_player = false;
	while (line)
	{
		line = get_next_line(map_file);
		j = 0;
		check_line(line, i, j, false);
		j++;
		free(line);
	}
	close(map_file);
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
