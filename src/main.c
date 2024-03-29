/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:01:29 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 22:21:16 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_data	*ft_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(t_data *data)
{
	data->map = ft_calloc(1, sizeof(t_map));
	data->tiles = ft_calloc(1, sizeof(t_tiles));
	data->player = ft_calloc(1, sizeof(t_player));
	data->keys = ft_calloc(1, sizeof(t_keys));
	data->ray = ft_calloc(1, sizeof(t_ray));
	data->keys->a = false;
	data->keys->d = false;
	data->keys->s = false;
	data->keys->w = false;
	data->keys->esc = false;
	data->keys->up = false;
	data->keys->down = false;
	data->keys->left = false;
	data->keys->right = false;
	if (!data->map)
		errors("Error allocating data");
	if (!data->tiles)
		errors("Error allocating data");
}

int	test1(void)
{
	hooks();
	raycasting();
	return (0);
}

int	launch_game(int width, int height)
{
	t_data	*data;

	data = ft_data();
	data->mlx_ptr = mlx_init();
	open_xpm(ft_data());
	if (!data->mlx_ptr)
		errors("Error initializing mlx");
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "Cub3d");
	if (!data->win_ptr)
		errors("Error starting mlx window");
	test1();
	return (0);
}

int	main(int ac, char **av)
{
	init_data(ft_data());
	valid_map(ac, av);
	launch_game(SCREEN_WIDTH, SCREEN_HEIGHT);
	key_press1(ft_data());
	clean_all(ft_data());
}
