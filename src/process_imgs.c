/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/28 23:51:39 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, new_x, new_y, color);
		i++;
	}
}

void	draw_player_rays(void)
{
	int	i;

	i = 0;
	float angle2 = ft_data()->player->dir - (ONE_DEGREE * 30);
	while (i < 120)
	{
		if (i == 60)
			draw_line(angle2, 1000, ft_data()->player->pos.x, ft_data()->player->pos.y, RED);
		else
			draw_line(angle2, 1000, ft_data()->player->pos.x, ft_data()->player->pos.y, WHITE);
		angle2 += ONE_DEGREE / 2;
		i++;
	}
}

static void	check_errors_xpm(void)
{
	if (!ft_data()->tiles->floor)
		errors("Error with xpm files");
	if (!ft_data()->tiles->wall)
		errors("Error with xpm files");
	if (!ft_data()->tiles->space)
		errors("Error with xpm files");
}


t_tiles_img	*init_tiles_img(void *mlx_ptr, char *path)
{
	t_tiles_img	*img;
	
	img = malloc(sizeof(t_tiles_img));
	if (!img)
		errors("Malloc failed");
	img->img = mlx_xpm_file_to_image(mlx_ptr, path, &img->width, &img->height);
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
	tiles->floor = init_tiles_img(mlx_ptr, FLOOR_TILE);
	tiles->wall = init_tiles_img(mlx_ptr, WALL_TILE);
	tiles->space = init_tiles_img(mlx_ptr, SPACE_TILE);
	tiles->player = init_tiles_img(mlx_ptr, PLAYER);
	check_errors_xpm();
}

void	render_tiles(void)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (ft_data()->map->map[++i])
	{
		j = -1;
		while (ft_data()->map->map[i][++j])
		{
			if (ft_data()->map->map[i][j] == WALL)
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr,
					ft_data()->tiles->wall, TILE_SIZE * j, TILE_SIZE * i);
			else if (ft_data()->map->map[i][j] == FLOOR
				|| ft_strchr(PLAYER_CHARS, ft_data()->map->map[i][j]))
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr,
					ft_data()->tiles->floor, TILE_SIZE * j, TILE_SIZE * i);
			else
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr,
					ft_data()->tiles->space, TILE_SIZE * j, TILE_SIZE * i);
		}
	}
	put_player();
}
