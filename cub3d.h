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

# define WIDTH 1000
# define HEIGHT 1000
# define PI 3.14159265359
# define SIZE 30
# define POV PI/3
# define MINIMAP_RANGE 4
# define MINIMAP_X 4
# define MINIMAP_Y 4

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
	float		x;
	float		y;
	float	new_x;
	float	new_y;
	int		speed;
	float	dir_x;
	float	dir_y;
	float	ray_y;
	float	ray_x;
	float	plane_x;
	float	plane_y;
	float	camera_x;
	float	angle;
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
	void    *wall_texture;
	char    *tex_data;
	int     tex_width;       // ancho de la textura
	int     tex_height;      // alto de la textura
	int     tex_bpp;         // bits por pixel
	int     tex_line_length; // cantidad de bytes por fila
	int     tex_endian;
}			t_cube;

void put_pixel(int x, int y, int color, t_cube *cubed);
void draw_square(int x, int y, int color, t_cube *cubed);
void draw_map(t_cube *cubed);
void draw_line_on_map(float x0, float y0, float x1, float y1, t_cube *cubed);
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
