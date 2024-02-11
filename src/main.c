/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:01:29 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/11 13:24:29 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* To do:

1. Finish map validation(gnl, etc)
2. Open window and draw map */

t_data	*ft_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(t_data *data)
{
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		errors("Error allocating data");
	data->map->rows = 1;
}

/* typedef struct s_map
{
	char		**map;
	bool		has_player;
	size_t		rows;
	size_t		cols;
}				t_map;

typedef struct s_data
{
	t_map		*map;
}				t_data; */

void	clean_all(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->map->rows)
	{
		free(data->map->map[i]);
		i++;
	}
	free(data->map->map);
	free(data->map);
}

int	main(int ac, char **av)
{
	//t_data	data;

	(void)ac;
	(void)av;
	init_data(ft_data());
	valid_map(ac, av);
	clean_all(ft_data());
}
