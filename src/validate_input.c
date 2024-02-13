/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:22:42 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/13 19:31:58 by diosanto         ###   ########.fr       */
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

void	get_player_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (ft_strchr(PLAYER_CHARS, data->map->map[i][j]))
			{
				data->player->pos.x = j * TILE_SIZE + 12;
				data->player->pos.y = i * TILE_SIZE + 12;
				//data->player->dir = data->map->map[i][j];
				data->map->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	save_map(char *map)
{
	get_nbr_rows(map, ft_data());
	ft_data()->map->map = malloc((ft_data()->map->rows + 1) * sizeof(char *));
	if (!ft_data()->map->map)
		errors("Error allocating map");
	get_lines(map, ft_data());
	get_player_pos(ft_data());
}

void	check_invalid_chars(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (!ft_strchr(ALLOWED_CHARS, data->map->map[i][j]))
				errors("Invalid character in map 😭");
			j++;
		}
		i++;
	}
}

void	check_borders(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (i == 0 || i == (data->map->rows - 1))
			{
				if (data->map->map[i][j] != '1')
					errors("Map must be surrounded by '1' 😭");
			}
			else if (j == 0 || j == (data->map->cols - 1))
			{
				if (data->map->map[i][j] != '1')
					errors("Map must be surrounded by '1' 😭");
			}
			j++;
		}
		i++;
	}
}

void	check_player(t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	player;

	i = 0;
	player = 0;
	while (i < data->map->rows)
	{
		j = 0;
		while (data->map->map[i][j])
		{
			if (ft_strchr(PLAYER_CHARS, data->map->map[i][j]))
			{
				if (player == 1)
					errors("Map must contain only one player 😭");
				player++;
			}
			j++;
		}
		i++;
	}
	if (player == 0)
		errors("Map must contain a player 😭");
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
	printf("Printing map in map_check() 🗺️\n");
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

//add flood_fill to check if empty spaces are isolated by walls

/*   1111111111
     1000000001
     1000011111
     100001    
     10000111111111111
1111110000000000000001
1000000111111000111101
10000001XXXX1000100001
100000011XXX1000100001
10E000001XXX1000000001
1111111111111111111111 

Replace ' ' with X*/

/* Check for invalid number of args
Check for invalid extension */
void	valid_map(int ac, char **av)
{
	if (ac != 2)
		errors("Invalid number of arguments 😭");
	else if (!valid_extension(av[1]))
		errors("File must be '.cub' 😭");
	map_check(av[1]);
	printf("Map is valid! 🎉\n");
}
