/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:02 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/14 20:06:05 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
			ft_data()->player->pos.x += 4;
	}
	else if (horizontal == true && dir == -1)
	{
		if (check_wall("left"))
			ft_data()->player->pos.x -= 4;
	}
	else if (horizontal == false && dir == 1)
	{
		if (check_wall("down"))
			ft_data()->player->pos.y += 4;
	}
	else if (horizontal == false && dir == -1)
	{
		if (check_wall("up"))
			ft_data()->player->pos.y -= 4;
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
