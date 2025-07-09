/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboiraza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 08:09:41 by iboiraza          #+#    #+#             */
/*   Updated: 2025/07/09 08:10:48 by iboiraza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_handler(t_cube *cubed)
{
	mlx_destroy_image(cubed->mlx, cubed->img_ptr);
	mlx_destroy_window(cubed->mlx, cubed->win);
	mlx_destroy_display(cubed->mlx);
	free(cubed->mlx);
	exit(EXIT_SUCCESS);
}

/*int is_wall(int x, int y)
{
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;

    if (map_x < 0 || map_x >= 10 || map_y < 0 || map_y >= 10)
        return 1; // Fuera del mapa => pared

    return 0;
}*/

int	key_press(int keysym, t_cube *cubed)
{
	if (keysym == XK_Escape)
		close_handler(cubed);
	if (keysym == XK_a)
		cubed->key_a = 1;
	else if (keysym == XK_d)
		cubed->key_d = 1;
	else if (keysym == XK_w)
		cubed->key_w = 1;
	else if (keysym == XK_s)
		cubed->key_s = 1;
	return (0);
}

int	key_release(int keysym, t_cube *cubed)
{
	if (keysym == XK_a)
		cubed->key_a = 0;
	else if (keysym == XK_d)
		cubed->key_d = 0;
	else if (keysym == XK_w)
		cubed->key_w = 0;
	else if (keysym == XK_s)
		cubed->key_s = 0;
	return (0);
}

/*int	key_handler(int keysym, t_cube *cubed)
{
	int new_x;
	int	new_y;

	new_x = cubed->x;
	new_y = cubed->y;

	if (keysym == XK_Escape)
		close_handler(cubed);
	if (cubed->x > 11 && keysym == XK_a)
		new_x -= cubed->speed;
	if (cubed->x < (WIDTH - 11) && keysym == XK_d)
		new_x += cubed->speed;
	if (cubed->y > 11 && keysym == XK_w)
		new_y -= cubed->speed;
	if (cubed->y < (HEIGHT - 11) && keysym == XK_s)
		new_y += cubed->speed;
//	cubed_render(cubed);
//	if (!is_wall(new_x, new_y))
//	{
		cubed->x = new_x;
		cubed->y = new_y;
//	}
//	clear_image(cubed);
//	mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
	//put_circle(cubed->x, cubed->y, 5, 0x00FF00, cubed);
	//draw_map(cubed);
//	put_player(cubed->x, cubed->y, 0x00FF00, cubed);
	//	put_pixel(cubed->x, cubed->y, 0xFFFFFF, cubed);
		return (0);
}*/
