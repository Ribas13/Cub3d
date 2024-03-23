/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:08:14 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/23 12:10:43 by micarrel         ###   ########.fr       */
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

void	ft_destroy_image(t_tiles_img *img)
{
	if (img->img)
		mlx_destroy_image(ft_data()->mlx_ptr, img->img);
	if (img)
		free(img);
}

void	free_image(t_data *data)
{
	if (data->tiles->north)
		ft_destroy_image(data->tiles->north);
	if (data->tiles->south)
		ft_destroy_image(data->tiles->south);
	if (data->tiles->west)
		ft_destroy_image(data->tiles->west);
	if (data->tiles->east)
		ft_destroy_image(data->tiles->east);
}

void	clean_all(t_data *data)
{
	free_array2(data->map->map);
	free_image(data);
	if (data->path_north)
		free(data->path_north);
	if (data->path_south)
		free(data->path_south);
	if (data->path_east)
		free(data->path_east);
	if (data->path_west)
		free(data->path_west);
	if (data->tiles)
		free(data->tiles);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	free(data->ray);
	free(data->map);
	free(data->player);
	free(data->mlx_ptr);
	free(data->keys);
}
