/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/02 00:13:24 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_texture_color(t_tiles_img *texture, int texture_x_offset, int texture_y)
{
	int	color;
	int	*arr;

	arr = (int *)texture->addr;
	color = arr[texture_y * texture->width + texture_x_offset];
	return (color);
}

void	draw_wall(int wall_start, int wall_end, int screen_x, t_tiles_img *texture, t_ray ray)
{
	int		screen_y;
	double	y_offset;
	int		texture_y;
	int		color;

	screen_y = 0;
	(void)ray;
	//(void)texture;
	//(void)y_offset;
	while (screen_y < SCREEN_HEIGHT)
	{
		while (screen_y < wall_start && screen_y < SCREEN_HEIGHT)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_x, screen_y, 0x87CEEB);
			screen_y++;
		}
		while (screen_y >= wall_start && screen_y < wall_end)
		{
			y_offset = (double)(screen_y - wall_start) / (wall_end - wall_start);
			texture_y = (int)(y_offset * texture->height);
			color = get_texture_color(texture, ray.texture_x_offset, texture_y);
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_x, screen_y, color);
			screen_y++;
		}
		while (screen_y < SCREEN_HEIGHT)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, screen_x, screen_y, 0x8B4513);
			screen_y++;
		}
		//screen_y++;
	}
}

void	draw_ray(t_ray ray)
{
	int wall_start = calculate_start(ray.distance);
	int wall_end = calculate_end(ray.distance);
	int screen_x = ray.section;
	int screen_x_end = ray.section + 10;

	while (screen_x <= screen_x_end)
	{
		draw_wall(wall_start, wall_end, screen_x, ray.texture, ray);
		screen_x++;
	}
}

char	calculate_wall_orientation(int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (y == map_y * TILE_SIZE)
		return ('N');
	else if (x == map_x * TILE_SIZE)
		return ('W');
	else if (y == ((map_y + 1) * TILE_SIZE) - 1)
		return ('S');
	else if (x == ((map_x + 1) * TILE_SIZE) - 1)
		return ('E');
	return ('0');
}

//Saves the ray distance, and x and y coordinates, ray angle and
//distance and wall orientation

t_tiles_img	*get_texture(char wall_orientation)
{
	if (wall_orientation == 'N')
		return (ft_data()->tiles->wall);
	else if (wall_orientation == 'E')
		return (ft_data()->tiles->wall);
	else if (wall_orientation == 'S')
		return (ft_data()->tiles->space);
	else if (wall_orientation == 'W')
		return (ft_data()->tiles->space);
	return (ft_data()->tiles->space);
}

t_ray	ray_properties(int i)
{
	t_ray	ray;

	ray.angle = ft_data()->player->dir - HALF_FOV + (i * HALF_DEGREE);
	ray.section = i * 10;
	ray.distance = ray_dist(ray.angle, 5000, ft_data()->player->pos.x,
			ft_data()->player->pos.y);
	ray.x = ft_data()->player->pos.x + ray.distance * cos(ray.angle);
	ray.y = ft_data()->player->pos.y + ray.distance * sin(ray.angle);
	ray.wall_orientation = calculate_wall_orientation(ray.x, ray.y);
	ray.distance = normalize_angle(ray);
	ray.texture = get_texture(ray.wall_orientation);
	if (ray.wall_orientation == 'N' || ray.wall_orientation == 'S')
		ray.texture_x_offset = (ray.x % TILE_SIZE) * (double)ray.texture->width / TILE_SIZE;
	else // ray.wall_orientation is 'E' or 'W'
		ray.texture_x_offset = (ray.y % TILE_SIZE) * (double)ray.texture->width / TILE_SIZE;
  return (ray);
}
/* 
void	end_threads()
{

}

void	*section_routine(void *thread)
{
	//while game is not over (ft_data()->game_over == false)
	
}

void	start_threads()
{
	pthread_t	threads[8];
	int			i;

	i = -1;
	while (++i < 8)
	{
		ft_data()->threads[i].thread = threads[i];
		ft_data()->threads[i].id = i;
		ft_data()->threads[i].starting_ray = i * 160;
		pthread_create(&threads[i], NULL, section_routine, &ft_data()->threads[i].thread);
	}
} */

/* Need to split the screen into 8 sections each of them will be handled by a thread
	Start the threads in the beggining of the program execution and send them to a loop
	inside draw_ray() there will be a check inside the loop that turns true once the player
	moves the camera and is changed to false once the key is not pressed anymore
	
	1. Create the threads inside the cast_rays()
	2. Send the threads to a function with an infinite loop (ideally only updates up
		to 60 times per second)
	3. Draw t_rays_x = true; (flag for each of the threads)  */

void	draw_ceiling(void)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, 0x87CEEB);
			y++;
		}
		x++;
	}
}

void	draw_floor(void)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = SCREEN_HEIGHT / 2;
		while (y < SCREEN_HEIGHT)
		{
			mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, x, y, 0x8B4513);
			y++;
		}
		x++;
	}
}

int	cast_rays(void)
{
	int		ray;
	int		sections;
	float	angle;

	hooks();
	ray = -1;
	angle = ft_data()->player->dir - HALF_FOV;
	sections = (FOV * (180 / PI)) * 2;
	while (++ray <= sections)
	{
		draw_ray(ray_properties(ray));
		angle += ONE_DEGREE / DEGREE_MULTIPLIER;
	}
	return (0);
}
