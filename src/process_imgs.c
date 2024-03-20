/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/20 16:29:40 by diosanto         ###   ########.fr       */
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

bool	first_intersection_h(t_ray *ray, int x, int y)
{
	int	i;

	i = 0;
	//printf("-----\n");
	ray->og_tile_y = (y / TILE_SIZE);
	while (i < 5000) //walks the line until the first horizontal line, will save the hitpoint coordinates in case of a wall hit
	{
		ray->new_x = x + i * cos(ray->angle);
		ray->new_y = y + i * sin(ray->angle);
		if (ray->new_x < 0 || ray->new_x > 1280)
			break ;
		else if (ray->new_y < 0 || ray->new_y > 720)
			break ;
		if ((int)ray->new_y / TILE_SIZE != ray->og_tile_y)
		{
			if (ft_data()->map->map[(int)ray->new_y / TILE_SIZE]
				[(int)ray->new_x / TILE_SIZE] == WALL)
			{
				//printf("Found wall\n");
				ray->h_distance = i;
				//printf("distance: %i\n", i);
				return (true);
				break ;
			}
			else
			{
				ray->x_hit1 = ray->new_x;
				ray->y_hit1 = ray->new_y;
				ray->new_x = x + i * cos(ray->angle);
				ray->new_y = y + i * sin(ray->angle);
				ray->h_distance = i;
				//printf("Horizontal axis hit point\n");
				break ;
			}

		}
		mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray->new_x, ray->new_y, WHITE);
		i++;
	}
	return (false);
}

bool	second_intersection_h(t_ray *ray, int x, int y)
{
	int	i;

	i = 0;
	//printf("-----\n");
	ray->og_tile_y = (y / TILE_SIZE);
	while (i < 5000) //walks the line until the first horizontal line, will save the hitpoint coordinates in case of a wall hit
	{
		ray->new_x = x + i * cos(ray->angle);
		ray->new_y = y + i * sin(ray->angle);
		if (ray->new_x < 0 || ray->new_x > 1280)
			break ;
		else if (ray->new_y < 0 || ray->new_y > 720)
			break ;
		if ((int)ray->new_y / TILE_SIZE != ray->og_tile_y)
		{
			if (ft_data()->map->map[(int)ray->new_y / TILE_SIZE]
				[(int)ray->new_x / TILE_SIZE] == WALL)
			{
				//printf("Found wall\n");
				ray->h_distance += i;
				//printf("distance: %i\n", i);
				return (true);
				break ;
			}
			else
			{
				//printf("2Horizontal axis hit point\n");
				ray->x_hit2 = ray->new_x;
				ray->y_hit2 = ray->new_y;
				ray->h_distance += i;
				break ;
			}

		}
		mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray->new_x, ray->new_y, GREEN);
		i++;
	}
	return (false);
}

float	calc_h(int p_x, int p_y, int r_x, int r_y)
{
	int	abs_x;
	int	abs_y;

	/* printf("map rows: %ld\n", ft_data()->map->rows);
	printf("map cols: %ld\n", ft_data()->map->cols); */
	if (r_x < 0)
		r_x = 0;
	else if (r_x > (int)ft_data()->map->cols * TILE_SIZE)
		r_x = ft_data()->map->cols * TILE_SIZE;
	if (r_y < 0)
		r_y = 0;
	else if (r_y > (int)ft_data()->map->rows * TILE_SIZE)
		r_y = ft_data()->map->rows * TILE_SIZE;
	abs_x = abs(p_x - r_x);
	abs_y = abs(p_y - r_y);
	printf("-----\n");
	printf("x: %d\n", p_x);
	printf("y: %d\n", p_y);
	printf("r_x: %d\n", r_x);
	printf("r_y: %d\n", r_y);
	printf("abs_y: %d\n", abs_y);
	printf("abs_x: %d\n", abs_x);
	printf("abs_y: %d\n", abs_y);
	printf("result: %f\n", sqrt((abs_x * abs_x) + (abs_y * abs_y)));
	printf("-----\n");
	return (sqrt((abs_x * abs_x) + (abs_y * abs_y)));
}

/* Right now we can walk the ray until the first two horizontal line collisions
Now we need to save both of the intersection coordinates and compare them to
save the offset*/
//still need to correctly set the cols and rows of the map
int	horizontal_dist(t_ray ray, int x, int y)
{
	int	i;

	i = 0;
	if (ray.angle < 0)
		ray.angle += 2 * PI;
	else if (ray.angle > 2 * PI)
		ray.angle -= 2 * PI;
	ray.found_h_wall = false;
	if (first_intersection_h(&ray, x, y) == true)
	{
		ray.h_distance = calc_h(x, y, ray.new_x, ray.new_y);
		return (0);
	}
	if (second_intersection_h(&ray, ray.new_x, ray.new_y) == true)
	{
		ray.h_distance = calc_h(x, y, ray.new_x, ray.new_y);
		return (0);
	}
	else
	{
		ray.x_offset = ray.x_hit2 - ray.x_hit1;
	}
	if (ray.angle > 0 && ray.angle < PI)
		ray.y_offset = 32;
	else
		ray.y_offset = -32;
	while (ft_data()->map->map[(int)ray.new_y / TILE_SIZE][(int)ray.new_x / TILE_SIZE] != WALL)
	{
		ray.new_x += ray.x_offset;
		ray.new_y += ray.y_offset;
		if ((int)ray.new_x / TILE_SIZE > (int)ft_data()->map->cols|| (int)ray.new_x < 0)
			break ;
		else if ((int)ray.new_y / TILE_SIZE > (int)ft_data()->map->rows|| (int)ray.new_y < 0)
			break ;
		/* printf("curr_tile_x: %d\n", (int)ray.new_x / TILE_SIZE);
		printf("curr_tile_y: %d\n", (int)ray.new_y / TILE_SIZE);
		printf("map_tiles_x: %d\n", (int)ft_data()->map->cols * TILE_SIZE);
		printf("map_tiles_y: %d\n", (int)ft_data()->map->rows * TILE_SIZE); */
		mlx_pixel_put(ft_data()->mlx_ptr,
			ft_data()->win_ptr, ray.new_x, ray.new_y, BLACK);
		i++;
	}
	ray.distance += i;
	ray.h_distance = calc_h(x, y, ray.new_x, ray.new_y);
	printf("distance: %d\n", ray.h_distance);
	return (0);
}

int	render_tiles(void)
{
	size_t	i;
	size_t	j;
	t_ray	ray;

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
		//put_player();
		//draw_line(ft_data()->player->dir, 30, ft_data()->player->pos.x, ft_data()->player->pos.y, WHITE);
		//draw_player_rays();
	}
	ray.angle = ft_data()->player->dir;
	//printf("Player x: %d y: %d\n", ft_data()->player->pos.x, ft_data()->player->pos.y);
	horizontal_dist(ray, ft_data()->player->pos.x, ft_data()->player->pos.y);
	//printf("Got to here\n");
	//sleep(5);
	return (0);
}
