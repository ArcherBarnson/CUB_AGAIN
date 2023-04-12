/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:00:17 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/12 17:39:33 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BAD_EXT	"Error :\nBad Extension\nExiting...\n"
# define NO_ARG		"Error :\nBad number of arguments\nExiting...\n"
# define IS_A_DIR	"Error :\nArgument is a directory\nExiting...\n"
# define OPEN_ERROR	"Error :\nCould not open map_file\
					\nCheck path and permissions\nExiting...\n"
# define EMPTY_FILE	"Error :\nFile is empty or cannot be read\nExiting...\n"

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
# define RES_Y 320
# define SPEED 6

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_player
{
	double	x;
	double	y;
	double	direction;
	double	speed;
}		t_player;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_map
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**map;
}		t_map;

typedef struct s_textures
{
	t_data	no_t;
	t_data	so_t;
	t_data	ea_t;
	t_data	we_t;
	int		f[3];
	int		c[3];
	int		fc[2];
	int		width;
	int		height;
}		t_textures;

typedef struct s_rays_info
{
	struct s_rays_info	*prev;
	double				rays;
	double				wich_rays;
	int					dist;
	int					pos_x;
	int					pos_y;
	int					side;
	struct s_rays_info	*next;
}	t_rays_info;

typedef struct s_pos // raycasting struct
{
	double		rays;
	double		tan;
	double		verti_y;
	double		verti_x;
	double		hori_y;
	double		hori_x;
	double		add_x;
	double		add_y;
	int			map_y;
	int			map_x;
	int			map_p;
	double		r;
	double		dist_verti;
	double		dist_hori;
	int			len_y;
	t_rays_info	*info;
}	t_pos;

typedef struct s_game
{
	int			keycode_w;
	int			keycode_a;
	int			keycode_s;
	int			keycode_d;
	int			keycode_l;
	int			keycode_r;
	char		**raw_map;
	t_map		*m;
	t_textures	*t;
	void		*mlx;
	void		*win;
	t_player	*p;
	t_data		*img;
	t_pos		*pos;
}		t_game;

typedef struct s_slice
{
	int		pos_x;
	int		wall_start;
	int		wall_end;
	int		side;
	double	wall_pos;
}		t_slice;

////////UTILS  ///////////////////////////
int			get_n_lines(int fd);
char		**alloc_raw_map(int fd);
int			is_a_valid_tile(char tile);
int			is_a_dir(char *filename);
char		**read_map(char *filename);
char		**get_map(char **raw_map);
//////////////////////////////////////////

////////MEMORY	//////////////////////////
t_game		*init_failure(t_game *g);
void		free_floodfill(int *sc, int *bc, char **pos_map);
void		exit_game(t_game *g);
//////////////////////////////////////////

////////PARSING //////////////////////////
int			check_extension(char *file);
void		free_tab(char **tab);
int			get_rgb(char *tile, int color);
int			skip_color_code(char *tile, int i);
int			get_color_code(char *id, int i);
int			get_hex_color(int rgb[3]);
char		*parse_id(char *id);
int			check_id_validity(t_game *g);
int			get_id(t_game *g, int i);
int			ft_parsing(t_game *g, char *filename);
int			load_textures(t_game *g);
t_game		*init_and_parse(int ac, char *map_file);
//////////////////////////////////////////

////////FLOODFILL/////////////////////////
int			get_tab_size(char **tab);
int			*get_player_coords(char **map);
int			*get_bounds_coords(char **map);
char		**init_pos_map(char **map);
int			flood(char **map, char **pos_map, int *p_pos, int *bounds_coords);
int			flood_x(char **map, char **pos_map, int *p_pos, int *bounds_coords);
int			flood_y(char **map, char **pos_map, int *p_pos, int *bounds_coords);
int			floodfill(char **map);
//////////////////////////////////////////

////////RENDER / MOVEMENT TESTS///////////
t_game		*init(void);
void		init_player_data(t_game *g);

double		angle_to_rad(double angle);
void		change_player_position(t_game *gd, int keycode);
void		reverse_player_position(t_game *gd, int keycode);
void		change_player_direction(t_game *gd, int keycode);
void		motion_control(t_game *gs, int keycode);
void		close_window(t_game *g);
int			player_in_wall(t_game *g, double next_x, double next_y);
int			keyboard_ctl_on(int keycode, t_game *gd);
int			keyboard_ctl_off(int keycode, t_game *gd);
int			get_keyboard_event(t_game *gd);
int			get_n_cols(char *line);
void		draw_tile(t_game *gd, int start_pos[2], int map_pos[2], int t);
void		draw_scene(t_game *gd);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		mlx_hooks(t_game *g);
int			eval_t_y(int y, int ws, double ratio);
void		eval_t_color(t_game *g, t_slice *slice, int y, double ratio);
t_data		*eval_tx_img(t_game *g, t_slice *slice);
void		render_image(t_game *g);
/////////////////////////////////////////

int			render_next_frame(t_game *gd);

/////// RAYCASTING ////////////
double		deg_to_rad(double a);
double		fixang(double a);
void		print_color_map(t_game *g, int x, int y);
void		insert_rays(t_game *g);
void		smallest_dist(t_pos *p, t_rays_info *info, t_game *g);
void		free_rays_info(t_rays_info *info);
///////////////////////////////
t_rays_info	*init_rays_info(t_pos *p, t_game *g);

#endif
