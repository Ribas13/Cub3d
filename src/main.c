/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:01:29 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/06 16:08:52 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* To do:

1. Finish map validation(gnl, etc)
2. Open window and draw map ✅
3. Draw ray casting middle line*/

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
	//data->tiles->floor = NULL;
	//data->tiles->wall = NULL;
	data->keys->a = false;
	data->keys->d = false;
	data->keys->s = false;
	data->keys->w = false;
	data->keys->esc = false;
	//data->keys->mouse_left = false;
	//data->keys->mouse_right = false;
	data->keys->up = false;
	data->keys->down = false;
	data->keys->left = false;
	data->keys->right = false;
	data->player->f_x = 0;
	data->player->f_y = 0;
	if (!data->map)
		errors("Error allocating data");
	if (!data->tiles)
		errors("Error allocating data");
}

int	launch_game(int width, int height)
{
	t_data	*data;

	data = ft_data();
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		errors("Error initializing mlx");
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "Cub3d");
	if (!data->win_ptr)
		errors("Error starting mlx window");
	//start_thread();
	open_xpm(ft_data());
	//render_tiles();
	cast_rays();
	return (0);
}

//need to calculate how many moves to change move player position no next tile

int	main(int ac, char **av)
{
	init_data(ft_data());
	valid_map(ac, av);
	launch_game(SCREEN_WIDTH, SCREEN_HEIGHT);
	key_press1(ft_data());
	clean_all(ft_data());
}
