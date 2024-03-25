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

void	errors2(char *error_msg, char **tmp)
{
	free_array(tmp);
	printf("Error\n");
	printf("%s\n", error_msg);
	clean_all(ft_data());
	exit(1);
}

/* Check for invalid number of args
Check for invalid extension */
void	valid_map(int ac, char **av)
{
	if (ac != 2)
		errors("Invalid number of arguments");
	else if (!valid_extension(av[1]))
		errors("File must be '.cub'");
	save_map(av[1]);
}

void	save_map(char *map)
{
	get_nbr_rows(map, ft_data());
	ft_data()->map->map = malloc((ft_data()->map->rows + 1) * sizeof(char *));
	if (!ft_data()->map->map)
		errors("Error allocating map");
	get_lines(map, ft_data());
	map_texture(ft_data());
	if (check_map(ft_data()) == false)
		errors("Invalid map");
	get_player_pos(ft_data());
}
