/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: micarrel <micarrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:00:35 by diosanto          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/20 16:43:54 by diosanto         ###   ########.fr       */
=======
/*   Updated: 2024/02/21 17:41:05 by micarrel         ###   ########.fr       */
>>>>>>> 99f9d2103fb0d9b24cafbff858e1bffd9d1b8502
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
# include <stdlib.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

//Imgs
# define WALL_TILE "./assets/wall.xpm"
# define FLOOR_TILE "./assets/floor.xpm"
# define SPACE_TILE "./assets/void.xpm"
# define PLAYER "./assets/player.xpm"
# define YELLOW 0xFFFF00
# define RED 0xFF0000

//For logic
# define PI 3.14159265358979323846
# define KEYPRESS_EVENT 2
# define DESTROY_NOTIFY_EVENT 17
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
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

typedef struct s_tiles_img
{
	void		*img;
	int			width;
	int			height;
}				t_tiles_img;

typedef struct s_tiles
{
	t_tiles_img	*wall;
	t_tiles_img	*space;
	char		*floor;
	char		*ceiling;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*sprite;
	void		*player;
}				t_tiles;

typedef struct s_map
{
	char		**map;
	bool		has_player;
	size_t		rows;
	size_t		cols;
}				t_map;

typedef struct s_player
{
	t_point		pos;
	double		delta_x;
	double		delta_y;
	double		dir;
	int			distance;
}				t_player;

typedef struct s_data
{
	t_map		*map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_tiles		*tiles;
	t_player	*player;
}				t_data;

//Prototypes

t_data	*ft_data(void);
int		map_texture(t_data *data);
bool	check_map(t_data *data);
void	valid_map(int ac, char **av);
void	errors(char *error_msg);
void	clean_all(t_data *data);
void	render_tiles(void);
void	key_press1(t_data *data);
void	update_player_pos(bool horizontal, int dir);
void	put_player(void);
bool	check_wall(char *dir);
void	cast_rays(void);






void	print_array(char **array);


#endif