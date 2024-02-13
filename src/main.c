/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:01:29 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/13 16:39:23 by diosanto         ###   ########.fr       */
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
	data->map = ft_calloc(1, sizeof(t_map));
	data->tiles = ft_calloc(1, sizeof(t_tiles));
	/* data->tiles->floor = NULL;
	data->tiles->wall = NULL; */
	if (!data->map)
		errors("Error allocating data");
}

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

void	launch_game(void)
{
	ft_data()->mlx_ptr = mlx_init();
	if (!ft_data()->mlx_ptr)
		errors("Error initializing mlx");
	ft_data()->win_ptr = mlx_new_window(ft_data()->mlx_ptr, 1280, 720, "Cub3d");
	if (!ft_data()->win_ptr)
		errors("Error starting mlx window");
	render_tiles();
	//mlx_loop(ft_data()->mlx_ptr);
	while (1)
	{
		continue;
	}
	//start_ray_casting();
}

int	main(int ac, char **av)
{
	init_data(ft_data());
	valid_map(ac, av);
	launch_game();
	clean_all(ft_data());
}
