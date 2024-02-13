/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:00:35 by diosanto          #+#    #+#             */
/*   Updated: 2024/02/13 16:43:58 by diosanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

//Imgs
# define WALL_TILE "./assets/wall.xpm"
# define FLOOR_TILE "./assets/floor.xpm"
# define SPACE_TILE "./assets/void.xpm"

//For logic
# define TILE_SIZE 32
# define ALLOWED_CHARS "10NSWE "
# define PLAYER_CHARS "NSWE"
# define WALL '1'
# define FLOOR '0'
# define SPACE ' '

//Structs
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_tiles
{
	void		*floor;
	void		*wall;
	void		*space;
}				t_tiles;

typedef struct s_map
{
	char		**map;
	bool		has_player;
	size_t		rows;
	size_t		cols;
}				t_map;

typedef struct s_data
{
	t_map		*map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_tiles		*tiles;
}				t_data;

//Prototypes

t_data	*ft_data(void);
void	valid_map(int ac, char **av);
void	errors(char *error_msg);
void	clean_all(t_data *data);
void	render_tiles(void);

#endif