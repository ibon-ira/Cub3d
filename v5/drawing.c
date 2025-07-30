/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 08:10:57 by iboiraza          #+#    #+#             */
/*   Updated: 2025/07/09 08:11:47 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void put_pixel(int x, int y, int color, t_cube *cubed)
{
	int	index;

    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;    
    index = y * cubed->line_length + x * cubed->bpp / 8;
    cubed->pixel_ptr[index] = color & 0xFF;
    cubed->pixel_ptr[index + 1] = (color >> 8) & 0xFF;
	cubed->pixel_ptr[index + 2] = (color >> 16) & 0xFF;
}

void draw_line_on_map(double x, double y, double x1, double y1, t_cube *cubed)
{
    double dx;
    double dy;
    double steps;
    double x_inc;
    double y_inc;
    int i;

    dx = cubed->ray_x - cubed->x;
    dy = cubed->ray_y - cubed->y;
    steps = fmax(fabs(dx), fabs(dy));
    x_inc = dx / steps;
    y_inc = dy / steps;
    i = -1;
    while (++i <= steps)
    {
        put_pixel(x, y, 0xC37777, cubed);
        x += x_inc;
        y += y_inc;
    }
}

void draw_square(int x, int y, int color, t_cube *cubed)
{
    int x2;
    int y2;

    y2 = y;
    x2 = x;
    while (y < (y2 + SIZE))
    {
        x = x2;
        while (x < (x2 + SIZE))
        {
            put_pixel (x, y, color, cubed);
            x++;
        }
        y++;
    }
}

void draw_map(t_cube *cubed)
{
    int y;
    int x;

    y = 0;
    while(cubed->map[y] != NULL)
    {
        x = 0;
        while(cubed->map[y][x] != '\0')
        {
            if (cubed->map[y][x] == '1')
                draw_square(x * SIZE, y * SIZE, 0x555555, cubed);
            else
                draw_square(x * SIZE, y * SIZE, 0xAAAAAA, cubed);
            x++;
        }
        y++;
    }
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}

/*void draw_map(t_cube *cubed)
{
    int y;
    int x;
    int draw_x;
    int draw_y;
    int y_max;

    y_max = 0;
    draw_y = 0;
    draw_x = 0;
    while (cubed->map[y_max])
        y_max++;
    y = (int)cubed->y - MINIMAP_Y;
    while(y <= (int)cubed->y + MINIMAP_Y)
    {
        x = (int)cubed->x - MINIMAP_X;
        draw_x = 0;
        while(x <= (int)cubed->x + MINIMAP_X)
        {
            if ((y >= 0 && y < y_max) && x >= 0 && x < ft_strlen(cubed->map[y]))
            {
                if (cubed->map[y][x] == '1')
                    draw_square(draw_x * SIZE, draw_y * SIZE, 0x555555, cubed);
                else if (cubed->map[y][x] == '0')
                    draw_square(draw_x * SIZE, draw_y * SIZE, 0xAAAAAA, cubed);
            }
            x++;
            draw_x++;
        }
        y++;
        draw_y++;
    }
}*/

/*void draw_map(t_cube *cubed)
{
    int start_y = (int)(cubed->y / SIZE) - MINIMAP_Y;
    int end_y = (int)(cubed->y / SIZE) + MINIMAP_Y;
    int start_x = (int)(cubed->x / SIZE) - MINIMAP_X;
    int end_x = (int)(cubed->x / SIZE) + MINIMAP_X;
    int map_height;

    int draw_y = 0;
    for (int y = start_y; y <= end_y; y++, draw_y++)
    {
        int draw_x = 1;
        for (int x = start_x; x <= end_x; x++, draw_x++)
        {
            
            if (y >= 0 && cubed->map[y] && x >= 0 && x < ft_strlen(cubed->map[y]))
            {
                printf("Dibujando celda [%d][%d]\n", y, x);
                int color = 0xAAAAAA; // Suelo
                if (cubed->map[y][x] == '1')
                    color = 0x555555; // Pared

                int screen_x = draw_x * SIZE;
                int screen_y = draw_y * SIZE;
                draw_square(screen_x, screen_y, color, cubed);
            }
        }
    }
}*/

void    draw_wall(int x, int start_y, int end_y, t_cube *cubed)
{
    double wall_x;
    int tex_x;
    int d;
    int tex_y;
    int offset;
    int color;

    t_texture *tex = cubed->current_tex;
    wall_x = cubed->wall_x - floor(cubed->wall_x);
    tex_x = (int)(wall_x * tex->width);
    if ((cubed->side == 0 && cubed->ray_dir_x > 0) || 
        (cubed->side == 1 && cubed->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    while (start_y < end_y)
        for (int y = start_y; y < end_y; y++)
    {
        d = y * 256 - HEIGHT * 128 + cubed->line_height * 128;
        tex_y = (d * tex->height) / cubed->line_height / 256;

        offset = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
        color = *(int *)(tex->data + offset);

        put_pixel(x, y, color, cubed);
        start_y++;
    }
}

void draw_3d_dda(int x, int start_y, int end_y, t_cube *cubed)
{
    int y;

    y = -1;
    while (++y < start_y)
        put_pixel(x, y, 0x87CEEB, cubed);
    draw_wall (x, start_y, end_y, cubed);
    y = end_y;
    while (y < HEIGHT)
    {
        put_pixel(x, y, 0x444444, cubed);
        y++; 
    }
}

void put_circle(int xc, int yc, int r, int color, t_cube *cubed)
{
    int x = 0;
    int d = 1 - r;
    int i;

    while (r >= x)
    {
        i = xc - x - 1;
        while(++i <= xc + x)
        {
            put_pixel(i, yc + r, color, cubed);
            put_pixel(i, yc - r, color, cubed);
        }
        i = xc - r - 1;
        while(++i <= xc + r)
        {
            put_pixel(i, yc + x, color, cubed);
            put_pixel(i, yc - x, color, cubed);
        }
        x++;
        if (d < 0)
            d = d + 2 * x + 1;
        else
            d = d + 2 * (x - --r) + 1;
    }
}

void clear_image(t_cube *cubed)
{
	int	y;
	int	x;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, cubed);
			x++;
		}
		y++;
	}
}
