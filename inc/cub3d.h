/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:00:35 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/20 00:16:51 by diosanto         ###   ########.fr       */
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
# include <pthread.h>

//Imgs
# define WALL_TILE "./assets/test1.xpm"
# define FLOOR_TILE "./assets/floor.xpm"
# define SPACE_TILE "./assets/test2.xpm"
# define PLAYER "./assets/player.xpm"
# define YELLOW 0xFFFF00
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define NORTH_WALL 0xB5C0D0
# define SOUTH_WALL 0xCCD3CA
# define EAST_WALL 0xF5E8DD
# define WEST_WALL 0xEED3D9

//60 degrees in radians = 1.0472

//For logic
# define MOTION_NOTIFY_EVENT 6
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define DEGREE_MULTIPLIER 4
# define MIN_DISTANCE 0.1
# define FOV 1.11701 // 64 degrees
# define HALF_FOV 0.558505 // 32 degrees
# define HALF_DEGREE 0.00872665
# define FOV_NORMAL 1.0472 //60 degrees
# define PI 3.14159265358979323846
# define ONE_DEGREE 0.017453292519943295
# define NINETY_DEGREES 1.5707963267948966
# define KEYPRESS_EVENT 2
# define KEYRELEASE_EVENT 3
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
# define WALL "1"
# define FLOOR "0"
# define SPACE " "

//Structs

typedef struct s_render
{
	int				id;
	pthread_t		thread;
	int				starting_ray;
}	t_render;

typedef struct s_keys
{
	bool			w;
	bool			a;
	bool			s;
	bool			d;
	bool			up;
	bool			down;
	bool			left;
	bool			right;
	bool			esc;
	int				mouse;
}	t_keys;

typedef struct s_point
{
	int				x;
	int				y;
}	t_point;

typedef struct s_tiles_img
{
	void			*img;
	int				width;
	int				height;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
}	t_tiles_img;

typedef struct s_tiles
{
	t_tiles_img		*wall;
	t_tiles_img		*space;
	t_tiles_img		*north;
	t_tiles_img		*south;
	t_tiles_img		*east;
	t_tiles_img		*west;
	t_tiles_img		*sprite;
	t_tiles_img		*player;
}	t_tiles;

typedef struct s_ray
{
	float			distance;
	float			v_distance;
	float			h_distance;
	float			angle;
	int				x;
	int				y;
	float			x_offset;
	float			y_offset;
	char			wall_orientation;
	int				section;
	double			hit_x;
	t_tiles_img		*texture;
	double			texture_x_offset;
}	t_ray;

typedef struct s_map
{
	char			**map;
	bool			has_player;
	size_t			rows;
	size_t			cols;
}	t_map;

typedef struct s_player
{
	t_point			pos;
	float			f_x;
	float			f_y;
	float			delta_x;
	float			delta_y;
	float			dir;
	float			distance;
}	t_player;

typedef struct s_data
{
	t_map			*map;
	void			*mlx_ptr;
	void			*win_ptr;
	t_tiles			*tiles;
	t_player		*player;
	t_keys			*keys;
	char			*path_north;
	char			*path_south;
	char			*path_east;
	char			*path_west;
	unsigned int	floor;
	unsigned int	ceiling;
	t_render		*thread_array;
	t_render		threads[8];
}	t_data;

//Prototypes

//exits

int			quit_game(void);
void		free_array(char **array);
void		clean_all(t_data *data);

//collision

int			check_wall(int key);
void		save_map(char *map);
bool		map_check(char *map);
bool		valid_extension(char *file);
void		get_lines(char *map, t_data *data);
void		get_nbr_rows(char *map, t_data *data);
void		get_player_pos(t_data *data);
t_tiles_img	*init_tiles_img(void *mlx_ptr, char *path);
int			launch_game(int width, int height);
void		hooks(void);

//mouse

int			mouse_move(void);
int			mouse_position(void);

//player_move

void		move_back(void);
void		move_forward(void);

void		render_tiles(void);
void		update_player_pos(bool horizontal, int dir);
void		put_player(void);

//Raycasting

t_data		*ft_data(void);
int			map_texture(t_data *data);
bool		check_map(t_data *data);
void		valid_map(int ac, char **av);
void		errors(char *error_msg);
void		key_press1(t_data *data);
void		print_array(char **array);
void		open_xpm(t_data *data);
//void		draw_line(float angle, int length, int x, int y, int color);
void		draw_player_rays(void);
int			on_press(int key);
int			cast_rays(void);
t_ray		ray_properties(int i);
char		calculate_wall_orientation(t_ray ray, int x, int y);
void		draw_ray(t_ray ray);
void		draw_wall_pixel(int x, int y, char wall_orientation);
int			calculate_start(float distance);
int			calculate_end(float distance);
float		ray_dist(float dir, int length, int x, int y);
float		normalize_angle(t_ray ray);
int			get_texture_color(t_tiles_img *texture,
				int texture_x_offset, int texture_y);

#endif