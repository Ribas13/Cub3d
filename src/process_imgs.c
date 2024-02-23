/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/23 17:27:18 by micarrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(float angle, int length, int x, int y)
{
	int	i;
	int	new_x;
	int	new_y;

	i = 0;
	while (i < length)
	{
		new_x = x + i * cos(angle);
		new_y = y + i * sin(angle);
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, new_x, new_y, WHITE);
		i++;
	}
}

int	ray_dist(float angle, int length, int x, int y)
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
		i++;
	}
	return (i);
}


//given a degree and distance, draw a square shape
//if the distance is bigger, smaller square(from the middle of  the screen)
//if the distance is smaller, bigger square(from the middle of the screen)
//each section is 60 pixels wide by 540 tall
//there is a total of 17 sections
void	draw_box(int degree, int distance)
{
	//start_x is the x position of the first pixel of the section
	//start_y is the y position of the first pixel of the section
	//middle is 540 / 2
	//distance is the distance from the wall
	//wall height is 540 / distance * 10
	int	start_x;
	int	start_y;
	int	middle;
	int	i;
	int	wall_height;

	middle = 540 / 2;
	start_x = degree * 60;
	wall_height = (540 / distance) * 50;
	start_y = middle - wall_height / 2;
	while (start_y < middle + wall_height / 2)
	{
		i = 0;
		while (i < 60)
		{
			if (distance < 300)
				mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, start_x + i,
					start_y, WHITE);
			else
				mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, start_x + i,
					start_y, BLACK);
			i++;
		}
		start_y++;
	}
}

//function to draw cast rays around the player in a 60 degree fov
//still need to add more rays, 60 is not enough
void	cast_rays(void)
{
	float	angle;
	int		i;
	int		x;
	int		y;

	i = 0;
	angle = ft_data()->player->dir - (FOV / 2);
	while (i < 60)
	{
		x = ft_data()->player->pos.x;
		y = ft_data()->player->pos.y;
		if (i == 30)
		{
			render_tiles();
			draw_line(angle, 5000, x, y);
		}
		draw_box(i, ray_dist(angle, 5000, x, y));
		angle += 0.0174533;
		i++;
	}
	//render_tiles();
	//put_player();
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

void	open_xpm(t_data *data)
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

// char *x and *y are used to not have leaks in the mlx_string_put function
/* void	render_tiles(void)
{
	size_t	i;
	size_t	j;
	char	*x;
	char	*y;

	i = -1;
	x = ft_itoa(ft_data()->player->pos.x);
	y = ft_itoa(ft_data()->player->pos.y);
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
		//put_player();
		//draw_line(ft_data()->player->dir, 5000, ft_data()->player->pos.x, ft_data()->player->pos.y);
		//mlx_string_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
		//	10, 10, 0x00FF0000, x);
		//mlx_string_put(ft_data()->mlx_ptr, ft_data()->win_ptr,
		//	10, 40, 0x00FF0000, y);
	}
	free(x);
	free(y);
} */

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
}
