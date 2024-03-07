/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:08:14 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/06 16:19:17 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	quit_game(void)
{
	clean_all(ft_data());
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static void	free_array2(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	clean_all(t_data *data)
{
	//int	i;

	free_array2(data->map->map);
	//mlx_destroy_image(data->mlx_ptr, data->tiles->floor);
	//mlx_destroy_image(data->mlx_ptr, data->tiles->wall);
	//mlx_destroy_image(data->mlx_ptr, data->tiles->space);
	//mlx_destroy_image(data->mlx_ptr, data->tiles->player);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->map);
	free(data->player);
	free(data->tiles);
	free(data->mlx_ptr);
	/* i = -1;
	while (++i < 4)
	{
		pthread_join(data->thread_array[i].thread, NULL);
	} */
}
