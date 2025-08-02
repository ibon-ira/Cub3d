/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:17:11 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 19:57:09 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	put_pixel(int x, int y, int color, t_map *mapa)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * mapa->line_length + x * mapa->bpp / 8;
	mapa->pixel_ptr[index] = color & 0xFF;
	mapa->pixel_ptr[index + 1] = (color >> 8) & 0xFF;
	mapa->pixel_ptr[index + 2] = (color >> 16) & 0xFF;
}

// void draw_line_on_map(double x, double y, double x1, double y1, t_map *mapa)
// {
//     double dx;
//     double dy;
//     double steps;
//     double x_inc;
//     double y_inc;
//     int i;

//     dx = mapa->ray_x - mapa->x;
//     dy = mapa->ray_y - mapa->y;
//     steps = fmax(fabs(dx), fabs(dy));
//     x_inc = dx / steps;
//     y_inc = dy / steps;
//     i = -1;
//     while (++i <= steps)
//     {
//         put_pixel(x, y, 0xC37777, mapa);
//         x += x_inc;
//         y += y_inc;
//     }
// }

void	draw_square(int x, int y, int color, t_map *mapa)
{
	int	x2;
	int	y2;

	y2 = y;
	x2 = x;
	while (y < (y2 + SIZE))
	{
		x = x2;
		while (x < (x2 + SIZE))
		{
			put_pixel (x, y, color, mapa);
			x++;
		}
		y++;
	}
}

void	draw_map(t_map *mapa)
{
	int	y;
	int	x;

	y = 0;
	while (mapa->map[y] != NULL)
	{
		x = 0;
		while (mapa->map[y][x] != '\0')
		{
			if (mapa->map[y][x] == '1')
				draw_square(x * SIZE, y * SIZE, 0x555555, mapa);
			else
				draw_square(x * SIZE, y * SIZE, 0xAAAAAA, mapa);
			x++;
		}
		y++;
	}
}

void	calculate_and_draw_pixel (t_map *mapa, int start_y, int tex_x, int x, t_texture *tex)
{
	int offset;
	int	color;
	int			tex_y;

	mapa->d = start_y * 256 - HEIGHT * 128 + mapa->line_height * 128;
	tex_y = (mapa->d * tex->height) / mapa->line_height / 256;
	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 ||
			tex_y >= tex->height)
	{
		start_y++;
		return ;
	}
	offset = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
	if (offset < 0 || offset + 3 >= tex->height * tex->line_len)
	{
		start_y++;
		return ;
	}
	color = *(int *)(tex->data + offset);
	put_pixel(x, start_y, color, mapa);
}

void	draw_wall(int x, int start_y, int end_y, t_map *mapa)
{
	double		wall_x;
	int			tex_x;
	t_texture	*tex;

	tex = mapa->current_tex;
	wall_x = mapa->wall_x - floor(mapa->wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((mapa->side == 0 && mapa->ray_dir_x < 0) ||
		(mapa->side == 1 && mapa->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	while (start_y < end_y)
	{
		calculate_and_draw_pixel(mapa, start_y, tex_x, x, tex);
		/*mapa->d = start_y * 256 - HEIGHT * 128 + mapa->line_height * 128;
		tex_y = (mapa->d * tex->height) / mapa->line_height / 256;
		if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 ||
				tex_y >= tex->height)
		{
			start_y++;
			continue ;
		}
		offset = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
		if (offset < 0 || offset + 3 >= tex->height * tex->line_len)
		{
			start_y++;
			continue ;
		}
		color = *(int *)(tex->data + offset);
		put_pixel(x, start_y, color, mapa);*/
		start_y++;
	}
}

void	draw_3d_dda(int x, int start_y, int end_y, t_map *mapa)
{
	int	y;

	y = -1;
	while (++y < start_y)
		put_pixel(x, y, 0x87CEEB, mapa);
	draw_wall (x, start_y, end_y, mapa);
	y = end_y;
	while (y < HEIGHT)
	{
		put_pixel(x, y, 0x444444, mapa);
		y++;
	}
}

void	clear_image(t_map *mapa)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, mapa);
			x++;
		}
		y++;
	}
}
