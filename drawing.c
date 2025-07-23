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

void draw_line_on_map(float x0, float y0, float x1, float y1, t_cube *cubed)
{
    float dx = x1 - x0;
    float dy = y1 - y0;
    float steps = fmax(fabs(dx), fabs(dy));
    float x_inc = dx / steps;
    float y_inc = dy / steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++)
    {
        put_pixel(x, y, 0xC37777, cubed);
        x += x_inc;
        y += y_inc;
    }
}

/*void draw_square(int x, int y, int size, int color, t_cube *cubed)
{
    for (int j = 0; j < size; j++)
        for (int i = 0; i < size; i++)
            put_pixel(x + i, y + j, color, cubed);
}

void draw_map(t_cube *cubed)
{
    for (int y = 0; y < 10; y++) // 10 filas
    {
        for (int x = 0; x < 10; x++) // 10 columnas
        {
            if (cubed->map[y][x] == 1)
                draw_square(x * 10, y * 10, 10, 0x555555, cubed); // gris oscuro
            else
                draw_square(x * 10, y * 10, 10, 0xAAAAAA, cubed); // gris claro (suelo)
        }
    }
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
}*/

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

/*void draw_map(t_cube *cubed)
{
    int y, x;

    int map_height = 0;
    while (cubed->map[map_height] != NULL)
        map_height++;

    int map_x = (int)(cubed->x / SIZE);
    int map_y = (int)(cubed->y / SIZE);
    int range = 4;

    int start_y = map_y - range;
    int end_y = map_y + range;

    if (start_y < 0) start_y = 0;
    if (end_y >= map_height) end_y = map_height - 1;

    y = start_y;
    while (y <= end_y)
    {
        int row_width = 0;
        while (cubed->map[y][row_width] != '\0')
            row_width++;

        int start_x = map_x - range;
        int end_x = map_x + range;
        if (start_x < 0) start_x = 0;
        if (end_x >= row_width) end_x = row_width - 1;

        x = start_x;
        while (x <= end_x)
        {
            if (cubed->map[y][x] == '1')
                draw_square(x * SIZE, y * SIZE, 0x555555, cubed);
            else
                draw_square(x * SIZE, y * SIZE, 0xAAAAAA, cubed);
            x++;
        }
        y++;
    }
}*/

/*void draw_map(t_cube *cubed)
{
    int y, x;
    int map_height = 0;
    while (cubed->map[map_height] != NULL)
        map_height++;

    int map_x = (int)(cubed->x / SIZE);
    int map_y = (int)(cubed->y / SIZE);

    int start_y = map_y - MINIMAP_RANGE;
    int end_y = map_y + MINIMAP_RANGE;

    if (start_y < 0) start_y = 0;
    if (end_y >= map_height) end_y = map_height - 1;

    y = start_y;
    while (y <= end_y)
    {
        int row_width = 0;
        while (cubed->map[y][row_width] != '\0')
            row_width++;

        int start_x = map_x - MINIMAP_RANGE;
        int end_x = map_x + MINIMAP_RANGE;
        if (start_x < 0) start_x = 0;
        if (end_x >= row_width) end_x = row_width - 1;

        x = start_x;
        while (x <= end_x)
        {
            // Aquí la clave: pintas en la ventana del minimapa,
            // no en la posición del mapa absoluta, sino relativa
            int screen_x = MINIMAP_X + (x - start_x) * SIZE;
            int screen_y = MINIMAP_Y + (y - start_y) * SIZE;

            if (cubed->map[y][x] == '1')
                draw_square(screen_x, screen_y, 0x555555, cubed);
            else
                draw_square(screen_x, screen_y, 0xAAAAAA, cubed);
            x++;
        }
        y++;
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

/*void put_circle(int xc, int yc, int r, int color, t_cube *cubed)
{
    int	x;
    int	y;
    int	d;
	
	x = -1;
	d = 1 - r;
	y = r;
    while (x++ <= y)
    {
        put_pixel(xc + x, yc + y, color, cubed);
        put_pixel(xc - x, yc + y, color, cubed);
        put_pixel(xc + x, yc - y, color, cubed);
        put_pixel(xc - x, yc - y, color, cubed);
        put_pixel(xc + y, yc + x, color, cubed);
        put_pixel(xc - y, yc + x, color, cubed);
        put_pixel(xc + y, yc - x, color, cubed);
        put_pixel(xc - y, yc - x, color, cubed);
        if (d < 0)
            d = d + 2*x + 1;
        else
        {
            y--;
            d = d + 2*(x - y) + 1;
        }
    }
}*/

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
