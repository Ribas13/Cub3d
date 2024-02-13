/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:24:20 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/13 16:44:18 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_errors_xpm(void)
{
	if (!ft_data()->tiles->floor)
		errors("Error with xpm files");
	if (!ft_data()->tiles->wall)
		errors("Error with xpm files");
}

static void	open_xpm(void)
{
	int	img_size;

	img_size = TILE_SIZE;
	ft_data()->tiles->floor = mlx_xpm_file_to_image(ft_data()->mlx_ptr, FLOOR_TILE, &img_size, &img_size);
	ft_data()->tiles->wall = mlx_xpm_file_to_image(ft_data()->mlx_ptr, WALL_TILE, &img_size, &img_size);
	ft_data()->tiles->space = mlx_xpm_file_to_image(ft_data()->mlx_ptr, SPACE_TILE, &img_size, &img_size);
	check_errors_xpm();
	
}

void	render_tiles(void)
{
	size_t	i;
	size_t	j;

	open_xpm();
	i = 0;
	while (i < ft_data()->map->rows)
	{
		j = 0;
		while (j < ft_data()->map->cols)
		{
			if (ft_data()->map->map[i][j] == WALL)
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr, ft_data()->tiles->wall, TILE_SIZE * j, TILE_SIZE * i);
			else if (ft_data()->map->map[i][j] == FLOOR)
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr, ft_data()->tiles->floor, TILE_SIZE * j, TILE_SIZE * i);
			else
				mlx_put_image_to_window(ft_data()->mlx_ptr, ft_data()->win_ptr, ft_data()->tiles->space, TILE_SIZE * j, TILE_SIZE * i);
			j++;
		}
		i++;
	}
}
