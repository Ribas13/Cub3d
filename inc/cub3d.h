/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diosanto <diosanto@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:00:35 by diosanto          #+#    #+#             */
/*   Updated: 2024/03/25 18:02:13 by diosanto         ###   ########.fr       */
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
# define WALL_TILE "./assets/wall.xpm"
# define FLOOR_TILE "./assets/floor.xpm"
# define SPACE_TILE "./assets/void.xpm"
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
# define TILE_SIZE 64
# define ALLOWED_CHARS "10NSWE "
# define PLAYER_CHARS "NSWE"
# define WALL "1"
# define FLOOR "0"
# define SPACE " "
# define ROTSPD 0.05

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
	double				x;
	double				y;
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
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
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
	t_tiles_img		*floor;
}	t_tiles;

typedef struct s_ray
{
	t_tiles_img		*texture;
	double			texture_x_offset;
	double			cam_x;
	double			dir_x;
	double			dir_y;
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	double			deltadist_x;
	double			deltadist_y;
	double			sidedist_x;
	double			sidedist_y;
	double			wall_dist;
	double			wall_x;
	int				side;
	int				start_draw;
	int				end_draw;
	int				line_height;
	char			wall_orientation;
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
	char			dir;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			screen_slice;
	double			x_max;
	double			y_max;
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
	t_ray			*ray;
}	t_data;

//Prototypes

//parser
char			**allocate_tmp(t_data *data);
int				ifnot_map(char str);
int				if_map(char str);
void			copy_non_empty_strings(t_data *data,
					char **tmp, int *i, int *j);
int				is_closed(int i, int j);
void			get_columns_lines(t_data *data, char **tmp);
int				adjust_count(char **tmp, int count);
int				map_verify(t_data *data);
void			errors2(char *error_msg, char **tmp);
unsigned int	rgb_to_hex(char *str, char **tmp);
bool			get_sidepath2(char **tmp, char *str, char *path, t_data *data);
int				rgb_verify(char *str);
int				empty_line(char *str);
int				ft_emptystr(char *str);
void			check_after(t_data *data, int *i, char **tmp);
void			map_texture_error_check(t_data *data, int i,
					int flag, char **tmp);

//exits

int				quit_game(void);
void			free_array(char **array);
void			clean_all(t_data *data);

//collision

void			save_map(char *map);
int				validate_map(void);
bool			valid_extension(char *file);
void			get_lines(char *map, t_data *data);
void			get_nbr_rows(char *map, t_data *data);
void			get_player_pos(t_data *data);
t_tiles_img		*init_tiles_img(void *mlx_ptr, char *path);
int				launch_game(int width, int height);
void			hooks(void);

//mouse

int				mouse_move(void);
int				mouse_position(void);

//player_move

void			move_back(void);
void			move_forward(void);
void			move_left(void);
void			move_right(void);
void			rotate(double rotspd);

//Raycasting

int				raycasting(void);
t_data			*ft_data(void);
int				map_texture(t_data *data);
bool			check_map(t_data *data, int i);
int				test1(void);
void			valid_map(int ac, char **av);
int				get_real_map(t_data *data, int i);
void			errors(char *error_msg);
void			key_press1(t_data *data);
char			set_ray_orientation(t_ray *ray);
void			open_xpm(t_data *data);
void			textures_updates(t_ray *ray, t_tiles_img *texture,
					int screen_slice);
t_tiles_img		*get_texture(char wall_orientation);
int				on_press(int key);
void			ray_properties(t_ray *ray, t_player *player, int screen_slice);
int				get_texture_color(t_tiles_img *texture,
					int texture_x_offset, int texture_y);

//init_player_dir.c

void			init_player_north(t_player *player);
void			init_player_east(t_player *player);
void			init_player_south(t_player *player);
void			init_player_west(t_player *player);

//validate_move

void			valid_move(t_data *data, double n_x, double n_y);
bool			is_valid_pos(t_data *data, double x, double y);

#endif