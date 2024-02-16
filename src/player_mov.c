/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/16 15:09:20 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(int beginX, int beginY, int endX, int endY)
{
	double	delta_x;
	double	delta_y;
	int		pixels;

	delta_x = endX - beginX;
	delta_y = endY - beginY;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(ft_data()->mlx_ptr, ft_data()->win_ptr, beginX, beginY, 0xFFFFFF);
		pixelX += delta_x;
		pixelY += delta_y;
		--pixels;
	}
}


//draw line from player to northenmost wall hit
void	cast_rays(void)
{
	//draw line from player in ft_data()->player->dir direction
	//loop it until it hits a wall
	
	draw_line(ft_data()->player->pos.x + 4, ft_data()->player->pos.y + 4, ft_data()->player->pos.x + 100 * cos(ft_data()->player->dir), ft_data()->player->pos.y + 100 * sin(ft_data()->player->dir));
}

bool	check_wall(char *dir)
{
	int	x;
	int	y;

	x = ft_data()->player->pos.x / TILE_SIZE;
	y = ft_data()->player->pos.y / TILE_SIZE;
	if (!ft_strncmp(dir, "up", 2))
	{
		if (ft_data()->map->map[y - 1][x] == WALL
			&& (ft_data()->player->pos.y - y * TILE_SIZE) < 4)
			return (false);
	}
	else if (!ft_strncmp(dir, "down", 4))
	{
		if (ft_data()->map->map[y + 1][x] == WALL
			&& (ft_data()->player->pos.y % TILE_SIZE) > 20)
			return (false);
	}
	else if (!ft_strncmp(dir, "left", 4))
	{
		if (ft_data()->map->map[y][x - 1] == WALL
			&& (ft_data()->player->pos.x - x * TILE_SIZE) < 4)
			return (false);
	}
	else if (!ft_strncmp(dir, "right", 5))
	{
		if (ft_data()->map->map[y][x + 1] == WALL
			&& (ft_data()->player->pos.x % TILE_SIZE) > 20)
			return (false);
	}
	return (true);

}

void	update_player_pos(bool horizontal, int dir)
{
	if (horizontal == true && dir == 1)
	{
		if (check_wall("right"))
			ft_data()->player->pos.x += 1;
	}
	else if (horizontal == true && dir == -1)
	{
		if (check_wall("left"))
			ft_data()->player->pos.x -= 1;
	}
	else if (horizontal == false && dir == 1)
	{
		if (check_wall("down"))
			ft_data()->player->pos.y += 1;
	}
	else if (horizontal == false && dir == -1)
	{
		if (check_wall("up"))
			ft_data()->player->pos.y -= 1;
	}
	render_tiles();
}

void	put_player(void)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (++i < ft_data()->map->rows)
	{
		j = -1;
		while (++j < ft_data()->map->cols)
		{
			if (ft_strchr(PLAYER_CHARS, ft_data()->map->map[i][j]))
			{
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr,
					ft_data()->tiles->player,
					ft_data()->player->pos.x, ft_data()->player->pos.y);
			}
		}
	}
}
