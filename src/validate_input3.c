/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validade_input3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:40:29 by micarrel          #+#    #+#             */
/*   Updated: 2024/03/18 00:40:29 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//add flood_fill to check if empty spaces are isolated by walls

/* Check for invalid number of args
Check for invalid extension */
void	valid_map(int ac, char **av)
{
	if (ac != 2)
		errors("Invalid number of arguments 😭");
	else if (!valid_extension(av[1]))
		errors("File must be '.cub' 😭");
	save_map(av[1]);
	printf("Map is valid! 🎉\n");
}

void	save_map(char *map)
{
	int i;
	int j;
	get_nbr_rows(map, ft_data());
	ft_data()->map->map = malloc((ft_data()->map->rows + 1) * sizeof(char *));
	if (!ft_data()->map->map)
		errors("Error allocating map");
	get_lines(map, ft_data());
	map_texture(ft_data());
	if (check_map(ft_data()) == false)
		errors("Invalid map aa  😭");
	get_player_pos(ft_data());
	//printf("Printing map in validate_input3.c\n");
	j = 0;
	for (i = 0; i < 10; i++)
	{
		if (!ft_data()->map->map[i])
			break ;
		for (j = 0; j < 10; j++)
		{
			if (ft_data()->map->map[i][j] == '\0')
			{
				//rows++;
				break ;
			}
			//printf("%c", ft_data()->map->map[i][j]);
		}
		//printf("\n");
	}
	ft_data()->map->cols = j;
	ft_data()->map->rows = i;
	//printf("Rows: %ld\n", ft_data()->map->rows);
	//printf("Cols: %ld\n", ft_data()->map->cols);
}
