/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/20 21:43:52 by diosanto         ###   ########.fr       */
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

//This is almost working, but still has some bugs
char	calculate_wall_orientation(t_ray ray, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (y == map_y * TILE_SIZE)
	{
		if (ft_data()->map->map[map_y - 1][map_x] == '1' && (ray.angle > PI / 2 && ray.angle < 3 * PI / 2))
			return ('E');
		else if (ft_data()->map->map[map_y][map_x - 1] == '0' && (ray.angle < PI / 2 || ray.angle > 3 * PI / 2))
			return ('W');
		return ('N');
	}
	else if (x == map_x * TILE_SIZE)
	{
		if (ft_data()->map->map[map_y][map_x - 1] == '1')
			return ('S');
		else if (ft_data()->map->map[map_y - 1][map_x] == '0')
			return ('N');
		return ('W');
	}
	else if (y == ((map_y + 1) * TILE_SIZE) - 1)
	{
		if (ft_data()->map->map[map_y + 1][map_x] == '1' && (ray.angle > PI / 2 && ray.angle < 3 * PI / 2))
			return ('E');
		else if (ft_data()->map->map[map_y][map_x - 1] == '0')
		{
			//printf("THIS\n");
			return ('S');
		}
		return ('S');
	}
	else if (x == ((map_x + 1) * TILE_SIZE) - 1)
	{
		if (ft_data()->map->map[map_y][map_x - 1] == '1')
			return ('W');
		return ('E');
	}
	return ('0');
}

//Esta e a tentativa atual de conjugar a orientacao do raio com sabermos se ele
//toca numa parede vertical ou horizontal, para veres o meu fix original usa a
//funcao da linha 26
/* if looking up and left can only be S or E wall
if looking up and right can only be S or W wall
if looking down and left can only be N or E
if looking down and right can only be N or W */
// char	calculate_wall_orientation(t_ray ray, int x, int y)
// {
// 	int	map_x;
// 	int	map_y;
// 	float	angle;

// 	map_x = x / TILE_SIZE;
// 	map_y = y / TILE_SIZE;
// 	angle = ray.angle;
// 	if (angle < 0)
// 		angle += 2 * PI;
// 	if (angle > 2 * PI)
// 		angle -= 2 * PI;
// 	(void)map_x;
// 	(void)map_y;
// 	//check for the direction first
// 	//printf("angle: %f\n", ray.angle);
// 	if (angle >= 0 && angle <= PI)
// 	{
// 		//looking down
// 		return ('N');
// 	}
// 	else if (angle < 2 *  PI && angle > PI)
// 	{
// 		if (angle > 3 * PI / 2) //looking up and right
// 		{
// 			if (ft_data()->map->map[map_y + 1][map_x] == '0')
// 				return ('S');
// 			else
// 				return ('E');
// 			/* if (ft_data()->map->map[map_y][map_x - 1] == '0'
// 				&& ft_data()->map->map[map_y + 1][map_x] != '0')
// 				return ('W');
// 			return ('S');*/
// 			//return ('S');
// 		}
// 		else
// 		{
// 			//looking up and left
// 			return ('N');
// 			/* if (ft_data()->map->map[map_y][map_x - 1] == '1')
// 				return ('S');
// 			else if (ft_data()->map->map[map_y][map_x + 1] == '1')
// 				return ('W'); */
// 			//return ('S');
// 		}
// 		//return ('S');
// 	}
// 	return ('0');
// }

t_tiles_img	*get_texture(char wall_orientation)
{
	if (wall_orientation == 'N')
		return (ft_data()->tiles->north);
	else if (wall_orientation == 'E')
		return (ft_data()->tiles->east);
	else if (wall_orientation == 'S')
		return (ft_data()->tiles->south);
	else if (wall_orientation == 'W')
		return (ft_data()->tiles->west);
	return (NULL);
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
	ray.h_distance = horizontal_dist(ray, ft_data()->player->pos.x,
			ft_data()->player->pos.y);
	ray.wall_orientation = calculate_wall_orientation(ray, ray.x, ray.y);
	ray.distance = normalize_angle(ray);
	ray.texture = get_texture(ray.wall_orientation);
	if (ray.wall_orientation == 'N' || ray.wall_orientation == 'S')
		ray.texture_x_offset = (ray.x % TILE_SIZE)
			* (double)ray.texture->width / TILE_SIZE;
	else
		ray.texture_x_offset = (ray.y % TILE_SIZE)
			* (double)ray.texture->width / TILE_SIZE;
	return (ray);
}

int	cast_rays(void)
{
	int		ray;
	int		sections;
	float	angle;
	t_ray	rays;

	hooks();
	ray = -1;
	angle = ft_data()->player->dir - HALF_FOV;
	sections = (FOV * (180 / PI)) * 2;
	while (++ray <= sections)
	{
		rays = ray_properties(ray);
		draw_ray(rays);
		//printf("ray: %d | angle: %f | distance: %f | x: %d | y: %d | wall_orientation: %c\n", ray, rays.angle, rays.distance, rays.x, rays.y, rays.wall_orientation);
		angle += ONE_DEGREE / DEGREE_MULTIPLIER;
	}
	//sleep(5);
	//errors("NADA");
	return (0);
}
