/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:08:14 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/15 20:05:54 by diosanto         ###   ########.fr       */
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

void	ft_destroy_image(t_tiles_img *img, char *path)
{
	if (img->img)
		mlx_destroy_image(ft_data()->mlx_ptr, img->img);
	if (path)
		free(path);
	if (img)
		free(img);
}

void	clean_all(t_data *data)
{
	free_array2(data->map->map);
	if (data->tiles->north)
		ft_destroy_image(data->tiles->north, data->path_north);
	if (data->tiles->south)
		ft_destroy_image(data->tiles->south, data->path_south);
	if (data->tiles->west)
		ft_destroy_image(data->tiles->west, data->path_west);
	if (data->tiles->east)
		ft_destroy_image(data->tiles->east, data->path_east);
	if (data->tiles)
		free(data->tiles);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->map);
	free(data->player);
	free(data->mlx_ptr);
	free(data->keys);
}
