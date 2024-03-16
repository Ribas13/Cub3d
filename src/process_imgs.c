/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/16 16:28:29 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
/* 
void	draw_line(float angle, int length, int x, int y, int color)
{
	int	i;
	int	new_x;
	int	new_y;

	i = 0;
	while (i < length)
	{
		new_x = x + i * cos(angle);
		new_y = y + i * sin(angle);
		if (ft_data()->map->map[(int)new_y / TILE_SIZE]
			[(int)new_x / TILE_SIZE] == WALL)
			break ;
		mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, new_x, new_y, color);
		i++;
	}
} */
/* 
void	draw_player_rays(void)
{
	int		i;
	float	angle2;

	i = 0;
	angle2 = ft_data()->player->dir - (ONE_DEGREE * 30);
	while (i < 120)
	{
		if (i == 60)
			draw_line(angle2, 1000, ft_data()->player->pos.x,
				ft_data()->player->pos.y, RED);
		else
			draw_line(angle2, 1000, ft_data()->player->pos.x,
				ft_data()->player->pos.y, WHITE);
		angle2 += ONE_DEGREE / 2;
		i++;
	}
} */

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
