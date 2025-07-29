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

/*int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}

void draw_map(t_cube *cubed)
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
