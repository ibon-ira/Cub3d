/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:33:46 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:16:06 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
# define CUB3_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <math.h>
#include <string.h>

# define RED 0xFF0000
# define GREEN 0xFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define YELLOW 0xFFFF00

# define WIDTH 1732
# define HEIGHT 1000
// # define WIDTH 1280
// # define HEIGHT 720
# define PI 3.14159265358979323846
# define SIZE 30
# define POV 1.17
# define MINIMAP_SIZE 0.2f
# define MINIMAP_X 8
# define MINIMAP_Y 4
# define W 119
# define A 97
# define S 115
# define D 100
# define ARGERROR "Debes introducir dos argumentos por terminal\n"
# define ARGERROR2 "Argumento vacio, especifica un mapa\n"
# define ARGERROR3 "El mapa tiene que acabar en .cub\n"
# define MAPERROR "Something went wrong copying the map\n"
# define MAPERROR2 "El mapa no se ha podido abrir\n"
# define MAPERROR3 "Error: Empty map\n"
# define MAPERROR4 "Map is not closed\n"
# define MAPERROR5 "North word is wrong\n"
# define MAPERROR6 "South word is wrong\n"
# define MAPERROR7 "West word is wrong\n"
# define MAPERROR8 "East word is wrong\n"
# define MAPERROR9 "Something went wrong checking atributes\n"
# define MAPERROR10 "Atribute not found\n"
# define MAP_ARG_DUP "Atribute is found more than once "
# define IMG "The image of one of the directions was not found in the system\n"
# define FORMAT "Tiene que tener nombre y extension .cub\n"
# define FORMAT2 "El nombre del mapa deberia ser printable\n"
# define FORMAT3 "There is some non digit character\n"
# define SPOTERROR "Should have only one player and map full with only 0 and 1\n"
# define MEMERROR "Memory allocation failed\n"
# define RGBERROR "There aren't three arguments after spliting\n"
# define RGBERROR2 "Some introduced number is not valid for rgb standard\n"
# define FLOOR "Floor character wrong\n"
# define CEILING "Ceiling character wrong\n"
# define NOPATH "No path to file to open\n"

// typedef struct s_complex
// {
// 	double	x;
// 	double	y;
// }				t_complex;

// typedef struct s_img
// {
// 	void	*img_ptr;
// 	char	*addr;
// 	int		bpp;
// 	int		line_len;
// 	int		endian;
// 	int     img_width;
//     int     img_height;
// }	t_img;

typedef struct s_texture {
    void    *img_ptr;
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
} t_texture;

typedef struct s_map
{
	// char	directions[4][200];
	// int		ndirections;
	char	*northtexture;
	char	*southtexture;
	char	*westtexture;
	char	*easttexture;
	// char	colors[2][200];
	// int		ncolors;
	char	*floorcolor;
	char	*ceilingcolor;
	int 	floor_color;
	int		ceiling_color;
	char	map[500][500];
	// int		nmap;
	char	*path;
	char	**final_map;
	char	**toflood_map;
	char	**spaceless_map;
//cosas de mapa
	int		map_height;
	int		map_width;

//keys
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
	int		wall_dir;

//estas x e ys son doubles pero en mi codigo no
	int		x;
	int		y;
	double	xx;
	double	yy;
	double	new_x;
	double	new_y;
//estas son int igual son las que yo uso
	int		map_x;
	int		map_y;
	int		d;
	int		end;

//valores de mapa
	int		speed;
	int		line_height;
	int		side;
	int		step_y;
	int		step_x;
	
//angulos y cositas varias de posicion
	double	wall_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	dir_x;
	double	dir_y;
	double	ray_y;
	double	ray_x;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	starting_angle;
	
//puede que estos column y row sean map_height y map width?
	int		column;
	int		row;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		line_length;
	int		endian;
	char	*name;	
	//texturas formato ibon
	t_texture tex_north;
    t_texture tex_south;
    t_texture tex_east;
    t_texture tex_west;
    t_texture *current_tex;
	// t_img   textures[4]; // 0: North, 1: South, 2: East, 3: West
}		t_map;

// typedef struct s_player
// {
// 	float y;
// 	float x;
// 	t_player player;
// }	t_player;

// t_complex	square_complex(t_complex z);
// t_complex	sum_complex(t_complex z1, t_complex z2);
// double		atod(char *s);

// double		escale(double element, double new_min,
// 				double new_max, double old_max);
// void		fractal_init(t_cube *fractal);
// void		fractal_render(t_cube *fractal);
// void		handle_pixel(int x, int y, t_cube *fractal);

// int			closewindow(t_cube *fractal);
// int			handle_key(int keysym, t_cube *fractal);
// int			handle_mouse(int button, int x, int y, t_cube *fractal);
// int			track_julia(int x, int y, t_cube *fractal);

// void		data_init(t_cube *fractal);
// void		fractal_init(t_cube *fractal);

int			ft_strcmp(char *s1, char *s2);
//freemem
void		ft_memdel(void *ptr);
// void		ft_memdel(void **ptr);
void		freeme(char **memory);
void    	freetextures(t_map *map);
// void		freeme(char ***memory);


//parselineutils.c
void		parsefloorceilingdirections(t_map *map, int i, int fd);

//asignatributes.c
int			asign_colors(t_map *map, char **arr);
int			asign_directions(t_map *map, char **arr);
//utils.c
int			ismap(char *str, t_map *map);
// void		directions_bridge(t_map *map, int *i, int fd);
void		directions_bridge(t_map *map, int i, int fd);
int			check3atributtes(t_map *map);
void		checkdirections(t_map *map, int i);
// void		fill_directions(t_map *map, int i, char *noendline);

//utils2.c
char		*noendl_dup(const char *s1);
// void		floornceiling(t_map *map, int *i, int fd);
void		floornceiling(t_map *map, int i, int fd);

void		mapcpy(t_map *map, int *i, int fd);
void		getfinalmap(t_map *map);
void		flood_staff(t_map *map);

//utils3.c
void		map4flood(t_map *map);
// int			checkns(t_map *map);
// int			checkns(t_map *map, int count);
int			checkns(t_map *map, int count, int i, int ii);
void		add_values(t_map *map, int i, int ii);
void		msg(int fd, char *str);
int			checkclosemap(t_map *map, int i, int ii);

//utils4.c
void		checkcolors(t_map *map, int i);
// void		isvalidnum(char **arr2);
int			isvalidnum(char **arr2);
// void		isrgbable(char **arr2);
int			isrgbable(char **arr2);
void		flood_fill(t_map *mapa, char **map, int x, int y);

void		freeall(t_map *map);
int			ft_is_nswe(char	c);
// int			flood_fill(char **map, int x, int y);
// void		get_row_column(t_map *map);
void		error(void);

//utils5.c
int			closewindow(t_map *mapa);
int			handle_key(int keysym, t_map *mapa);
int 		checkmap_name_folders(char *str);
int			check_printable_map_name(char *str, int i, int ii);
void		know_starting_angle(t_map *map, int i, int ii);

//utils6.c
int			key_release(int keysym, t_map *mapa);
int			cubed_render(t_map *mapa);
void		rotate_cubed (t_map *mapa);
void		set_player_dir_and_plane(t_map *mapa);
int			is_wall(t_map *mapa, double pos_x, double pos_y);

//utils7.c
int	key_release(int keysym, t_map *mapa);
int	key_press(int keysym, t_map *mapa);
int	parse_color(const char *line);

//drawing.c
void	clear_image(t_map *mapa);
void	draw_3d_dda(int x, int start_y, int end_y, t_map *mapa);
void	put_circle(int xc, int yc, int r, int color, t_map *mapa);
void	draw_wall(int x, int start_y, int end_y, t_map *mapa);
void	draw_square(int x, int y, int color, t_map *mapa);
void	draw_line_on_map(double x, double y, double x1, double y1, t_map *mapa);
void	put_pixel(int x, int y, int color, t_map *mapa);

//raycasting.c
void	raycasting(t_map *mapa, int i);
void	select_texture(t_map *mapa);
// void	calculate_wall_data(t_map *mapa, double *dist, double *wall_x);
void	init_dda(t_map *mapa, double *side_dist_x, double *side_dist_y);
int		perform_dda(t_map *mapa, double *side_dist_x, double *side_dist_y);
void	calculate_wall_data(t_map *mapa, double *dist);

#endif