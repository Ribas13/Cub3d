/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/22 23:08:27 by micarrel         ###   ########.fr       */
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
		printf("----\n");
		printf("draw_line\n");
		printf("x: %d\n", new_x);
		printf("y: %d\n", new_y);
		printf("----\n");
		if (ft_data()->map->map[(int)new_y / TILE_SIZE]
			[(int)new_x / TILE_SIZE] == WALL)
			break ;
		mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, new_x, new_y, color);
		i++;
	}
}

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
}

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

static void	open_xpm2(t_data *data)
{
	int		img_s;
	void	*mlx_ptr;
	t_tiles	*tiles;

	img_s = TILE_SIZE;
	tiles = data->tiles;
	mlx_ptr = data->mlx_ptr;
	tiles->floor = mlx_xpm_file_to_image(mlx_ptr, FLOOR_TILE, &img_s, &img_s);
	tiles->wall = mlx_xpm_file_to_image(mlx_ptr, WALL_TILE, &img_s, &img_s);
	tiles->space = mlx_xpm_file_to_image(mlx_ptr, SPACE_TILE, &img_s, &img_s);
	tiles->player = mlx_xpm_file_to_image(mlx_ptr, PLAYER, &img_s, &img_s);
	check_errors_xpm();
}

int	render_tiles(void)
{
	size_t	i;
	size_t	j;
	//t_ray	ray;

	open_xpm2(ft_data());
	i = -1;
	//ft_data()->map->rows = 8;
	while (++i < ft_data()->map->rows)
	{
		j = -1;
		while (++j < ft_data()->map->cols)
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
	/* ray.angle = ft_data()->player->dir;
	ray.a_cos = cos(ray.angle);
	ray.a_sin = sin(ray.angle);
	ray.h_distance = horizontal_dist(ray, ft_data()->player->pos.x, ft_data()->player->pos.y);
	printf("Horizontal distance: %d\n", ray.h_distance);
	ray.v_distance = vertical_dist(ray, ft_data()->player->pos.x, ft_data()->player->pos.y);
	printf("Vertical distance: %d\n", ray.v_distance); */
	return (0);
}
