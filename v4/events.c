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
	else if (keysym == XK_Left)
		cubed->key_left = 1;
	else if (keysym == XK_Right)
		cubed->key_right = 1;
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
	else if (keysym == XK_Left)
		cubed->key_left = 0;
	else if (keysym == XK_Right)
		cubed->key_right = 0;
	return (0);
}
