/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:23:21 by iboiraza          #+#    #+#             */
/*   Updated: 2025/07/07 15:23:50 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H


# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1732
# define HEIGHT 1000
# define PI 3.14159265359
# define SIZE 30
# define POV 1.17
# define MINIMAP_RANGE 4
# define MINIMAP_X 4
# define MINIMAP_Y 4
# define NORTH 0
# define SOUTH 1
# define EAST  2
# define WEST  3

typedef struct s_texture {
    void    *img_ptr;
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
} t_texture;

typedef struct s_cube
{
	char	*name;
	void	*mlx;
	void	*win;
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		line_length;
	int		endian;
//	t_img	img;
	char		**map;
	int		map_height;
	int		map_width;
	char	start;
	int		minimap_width;
	int		minimap_height;
	double		x;
	double		y;
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;
	int		speed;
	int		line_height;
	int		side;
	int		step_y;
	int		step_x;
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
	double	angle;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
	int		wall_dir;
	t_texture tex_north;
    t_texture tex_south;
    t_texture tex_east;
    t_texture tex_west;
    t_texture *current_tex;
	int     tex_width;       // ancho de la textura
	int     tex_height;      // alto de la textura
	int     tex_bpp;         // bits por pixel
	int     tex_line_len; // cantidad de bytes por fila
	int     tex_endian;
}			t_cube;

void put_pixel(int x, int y, int color, t_cube *cubed);
void draw_square(int x, int y, int color, t_cube *cubed);
void draw_map(t_cube *cubed);
void draw_line_on_map(double x0, double y0, double x1, double y1, t_cube *cubed);
void put_circle(int xc, int yc, int r, int color, t_cube *cubed);
void clear_image(t_cube *cubed);
int	close_handler(t_cube *cubed);
//int is_wall(int x, int y);
int	key_release(int keysym, t_cube *cubed);
int	key_handler(int keysym, t_cube *cubed);
int	key_press(int keysym, t_cube *cubed);
/*int key_press(int keysym, t_player *player);
int key_release(int keysym, t_player *player);
int	key_handler(int keysym, t_data *cubed);
int	close_handler(t_data *cubed);
void move_player(t_player *player);
*/
#endif
