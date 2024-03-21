/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:59:30 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/21 18:28:30 by diosanto         ###   ########.fr       */
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

/* 1. check for straight angle */
void	set_ray_distance(t_ray *ray)
{

	ray->h_distance = horizontal_dist(*ray, ft_data()->player->pos.x,
			ft_data()->player->pos.y);
	ray->v_distance = vertical_dist(*ray, ft_data()->player->pos.x,
			ft_data()->player->pos.y);
	if (ray->h_distance <= ray->v_distance) //checck if they are equal
	{
		if (ray->angle >= 0 && ray->angle <= PI)
			ray->wall_orientation = 'N';
		else
			ray->wall_orientation = 'S';
		ray->distance = ray->h_distance;
		return ;
	}
	else
	{
		if (ray->angle >= PI / 2 && ray->angle <= 3 * PI / 2)
			ray->wall_orientation = 'E';
		else
			ray->wall_orientation = 'W';
		ray->distance = ray->v_distance;
		return ;
	}
}

t_ray	ray_properties2(int i)
{
	t_ray	ray;

	ray.i = i;
	ray.angle = ft_data()->player->dir - HALF_FOV + (i * HALF_DEGREE);
	ray.angle = set_angle(ray.angle);
	ray.a_cos = cos(ray.angle);
	ray.a_sin = sin(ray.angle);
	ray.section = i * 10;

	printf("before set_ray_distance\n");
	set_ray_distance(&ray);
	printf("after set_ray_distance\n");



	ray.x = ft_data()->player->pos.x + ray.distance * ray.a_cos;
	ray.y = ft_data()->player->pos.y + ray.distance * ray.a_sin;

	/* if (i == 63)
	{
		printf("------------------\n");
		printf("ray_x: %d | ray_y: %d\n", ray.x, ray.y);
		printf("ray_angle: %f\n", ray.angle);
		printf("h_distance: %d\n", ray.h_distance);
		printf("v_distance: %d\n", ray.v_distance);
		if (ray.h_distance < ray.v_distance)
			printf("hit horizontal wall\n");
		else
			printf("hit vertical wall\n");
		printf("------------------\n");
	} */

	//ray.distance = normalize_angle(ray);
	//ray.texture = get_texture(ray.wall_orientation);
	/* if (ray.wall_orientation == 'N' || ray.wall_orientation == 'S')
		ray.texture_x_offset = (ray.x % TILE_SIZE)
			* (double)ray.texture->width / TILE_SIZE;
	else
		ray.texture_x_offset = (ray.y % TILE_SIZE)
			* (double)ray.texture->width / TILE_SIZE; */
	return (ray);
}

void	solve_conflict(t_ray *ray)
{
	t_ray	next_ray;
	t_ray	prev_ray;

	next_ray = ray_properties2(ray->i + 1);
	prev_ray = ray_properties2(ray->i - 1);
	printf("solving the conflict\n");
	if (next_ray.wall_orientation == prev_ray.wall_orientation)
		ray->wall_orientation = next_ray.wall_orientation;
	ray->wall_orientation = next_ray.wall_orientation;
	printf("solved\n");
	//need to find another way to solve the conflict
	//(void)ray;
	return ;
}

t_ray	ray_properties(int i)
{
	t_ray	ray;

	ray.i = i;
	ray.angle = ft_data()->player->dir - HALF_FOV + (i * HALF_DEGREE);
	ray.angle = set_angle(ray.angle);
	ray.a_cos = cos(ray.angle);
	ray.a_sin = sin(ray.angle);
	ray.section = i * 10;

	printf("before set_ray_distance\n");
	set_ray_distance(&ray);
	printf("after set_ray_distance\n");



	ray.x = ft_data()->player->pos.x + ray.distance * ray.a_cos;
	ray.y = ft_data()->player->pos.y + ray.distance * ray.a_sin;
	printf("before conflict\n");
	if (i == 63 && ray.x == ray.y)
	{
		printf("------------------\n");
		printf("ray_x: %d | ray_y: %d\n", ray.x, ray.y);
		printf("ray_angle: %f\n", ray.angle);
		printf("h_distance: %d\n", ray.h_distance);
		printf("v_distance: %d\n", ray.v_distance);
		if (ray.h_distance < ray.v_distance)
			printf("hit horizontal wall\n");
		else
			printf("hit vertical wall\n");
		printf("------------------\n");
	}
	if (ray.x == ray.y)
	{
		solve_conflict(&ray);
	}
	printf("after conflict\n");

	//ray.distance = normalize_angle(ray);
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
		angle += ONE_DEGREE / DEGREE_MULTIPLIER;
	}
	return (0);
}
