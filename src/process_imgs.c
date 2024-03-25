/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/24 22:20:13 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_errors_xpm(void)
{
	if (!ft_data()->tiles->north->img || !ft_data()->tiles->south->img
		|| !ft_data()->tiles->west->img || !ft_data()->tiles->east->img)
		errors("XPM file not found");
}

t_tiles_img	*init_tiles_img(void *mlx_ptr, char *path)
{
	t_tiles_img	*img;

	img = malloc(sizeof(t_tiles_img));
	if (!img)
		errors("Malloc failed");
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
	if (!img->img)
		return (img);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->size_line, &img->endian);
	return (img);
}

void	open_xpm(t_data *data)
{
	void	*mlx_ptr;
	t_tiles	*tiles;

	tiles = data->tiles;
	mlx_ptr = data->mlx_ptr;
	tiles->north = init_tiles_img(mlx_ptr, data->path_north);
	tiles->south = init_tiles_img(mlx_ptr, data->path_south);
	tiles->west = init_tiles_img(mlx_ptr, data->path_west);
	tiles->east = init_tiles_img(mlx_ptr, data->path_east);
	check_errors_xpm();
}
