/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:00:17 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/30 04:19:25 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//parsing error code :
//	1 - file error
//	2 - texture error
//	3 - map error

# define BAD_EXT	"Error :\nBad Extension\nExiting...\n"
# define NO_ARG		"Error :\nBad number of arguments\nExiting...\n"
# define IS_A_DIR	"Error :\nArgument is a directory\nExiting...\n"
# define OPEN_ERROR	"Error :\nCould not open map_file\nCheck path and permissions\nExiting...\n"

# define BAD_ID		"Error :\nInvalid identifier\nExiting...\n"
# define MAP_ERR	"Error :\nInvalid map\nExiting...\n"

# define T_LOAD_ERROR	"Error :\nCould not load textures\nExiting...\n"

# define RED 		0x00FF0000
# define BLUE 		0x000000FF
# define GREEN 		0x0000FF00
# define TEST 0xFFFFFFF
# define TEST_2 0xFFFFF00
# define TILE_SIZE	64
# define TILE_SIZE_F	64.0
# define ESC 		65307
# define W 		119
# define A 		97
# define S 		115
# define D 		100
# define LEFT 		65361
# define RIGHT 		65363
# define P_COS 		"cos(angle_to_rad(gd->playr.direction))"
# define P_SIN 		"sin(angle_to_rad(gd->playr.direction))"
# define TEXTURE_WIDTH 	64
# define TEXTURE_HEIGHT	64
# define AC_BLACK "\x1b[30m"
# define AC_RED "\x1b[31m"
# define AC_GREEN "\x1b[32m"
# define AC_YELLOW "\x1b[33m"
# define AC_BLUE "\x1b[34m"
# define AC_MAGENTA "\x1b[35m"
# define AC_CYAN "\x1b[36m"
# define AC_WHITE "\x1b[37m"
# define AC_NORMAL "\x1b[m"
# define RES_X 1080
# define RES_Y 720
# define SPEED 6



# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
/*
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;
*/
/*
typedef struct s_texture	//structure nulle jsais pas pk c'etait la cette daube
{
	char	*path;		//ca sert a rien ca
	void	*img;
	int		height;
	int		width;
}		t_texture;
*/

typedef struct s_player
{
	double		x;
	double		y;
	double	direction;	//must be converted to radian
	double	speed;
}		t_player;

typedef	struct	s_data		//mlx imgs struct
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_map		//map ids and tiles struct
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*f;
	char		*c;
	char		**map;
}		t_map;

typedef struct s_textures
{
	t_data	no_t;		//
	t_data	so_t;		//
	t_data	ea_t;		//
	t_data	we_t;		//
	int	f[3];
	int	c[3];
	int	fc[2];
	int	width;
	int	height;
}		t_textures;

typedef struct s_game		//main struct (keycodes, player_data and secondary structs)
{
	int			keycode_w;
	int			keycode_a;
	int			keycode_s;
	int			keycode_d;
	int			keycode_l;
	int			keycode_r;
	char			**raw_map;
	t_map		*m;
	t_textures	*t;
	void		*mlx;
	void		*win;
	t_player	*p;
	t_data		*img;		//might be useful for later (NOT THE TEXTURES IMAGES)
}		t_game;

typedef struct s_rays_info
{
	struct s_rays_info *prev;
	float	rays;
	float	wich_rays;
	int		dist;
	int		pos_x;
	int		pos_y;
	struct s_rays_info *next;
}	t_rays_info;

typedef struct s_slice
{
	int	pos_x;
	int	wall_start;
	int	wall_end;
	float	wall_pos;
}		t_slice;

typedef struct s_pos // raycasting struct
{
	float		rays;
	float		tan;
	float		r_y;//to_remove
	float		r_x;//to_remove
	float		verti_y;
	float		verti_x;
	float		hori_y;
	float		hori_x;
	float		add_x;
	float		add_y;
	int			map_y;
	int			map_x;
	int			map_p;
	float		r;
	float			dist_verti;
	float			dist_hori;
	int			len_y;
	t_rays_info	*info;
}	t_pos;

////////UTILS  ///////////////////////////
int	get_n_lines(int fd);
char	**alloc_raw_map(int fd);
int	is_a_valid_tile(char tile);
char	**read_map(char *filename);
char	**get_map(char **raw_map);
//////////////////////////////////////////

////////PARSING //////////////////////////
int	check_extension(char *file);
void	free_tab(char **tab);
int	get_rgb(char *tile, int color);
int	skip_color_code(char *tile, int i);
int	get_color_code(char *id, int i);
int	get_hex_color(int rgb[3]);
char	*parse_id(char *id);
int	check_id_validity(t_game *g);
int	get_id(t_game *g, int i);
int	ft_parsing(t_game *g, char *filename);
int	load_textures(t_game *g);
t_game	*init_and_parse(int ac, char *map_file);
//////////////////////////////////////////

////////FLOODFILL/////////////////////////
int	get_tab_size(char **tab);					//put that shit in utils
int	*get_player_coords(char **map);
int	*get_bounds_coords(char **map);
char	**init_pos_map(char **map);
int	flood_x(char **map, char **pos_map, int *p_pos, int *bounds_coords);
int	flood_y(char **map, char **pos_map, int *p_pos, int *bounds_coords);
int	flood(char **map, char **pos_map, int *p_pos, int *bounds_coords);
int	floodfill(char **map);
//////////////////////////////////////////

////////RENDER / MOVEMENT TESTS///////////
t_game	*init(void);
void	init_player_data(t_game *g);

double	angle_to_rad(double angle);
void	change_player_position(t_game *gd, int keycode);
void	reverse_player_position(t_game *gd, int keycode);
void	change_player_direction(t_game *gd, int keycode);
void	motion_control(t_game *gs, int keycode);
int	keyboard_ctl_on(int keycode, t_game *gd);
int	keyboard_ctl_off(int keycode, t_game *gd);
int	get_keyboard_event(t_game *gd);
int		get_n_cols(char *line);
void	draw_tile(t_game *gd, int start_pos[2], int map_pos[2], int title_size);
void	draw_scene(t_game *gd);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	mlx_hooks(t_game *g);

void	render_image(t_game *g);
/////////////////////////////////////////

int		render_next_frame(t_game *gd);

/////// RAYCASTING ////////////
float		deg_to_rad(float	a);
int			fix_ang(int	a);
void		print_line(int x0, int y0, int x1, int y1, t_game *g, int color); // not important
void		print_color_map(t_game *g, int x, int y); // not important
t_pos		*insert_rays(t_game *g);
void	smallest_dist(t_pos *p, t_rays_info *info, t_game *g);
t_rays_info	*init_rays_info(t_pos *p, t_game *g);
///////////////////////////////
#endif

