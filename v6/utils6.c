/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 17:37:59 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:04:41 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

// int	key_release(int keysym, t_map *mapa)
// {
// 	if (keysym == XK_a)
// 		mapa->key_a = 0;
// 	else if (keysym == XK_d)
// 		mapa->key_d = 0;
// 	else if (keysym == XK_w)
// 		mapa->key_w = 0;
// 	else if (keysym == XK_s)
// 		mapa->key_s = 0;
// 	else if (keysym == XK_Left)
// 		mapa->key_left = 0;
// 	else if (keysym == XK_Right)
// 		mapa->key_right = 0;
// 	return (0);
// }

int	is_wall(t_map *mapa, double pos_x, double pos_y)
{
	if (mapa->final_map[(int)(pos_y + 0.8) / SIZE][(int)(pos_x + 0.8)
			/ SIZE] == '1' ||
			mapa->final_map[(int)(pos_y + 0.8) / SIZE][(int)(pos_x - 0.8)
			/ SIZE] == '1' ||
			mapa->final_map[(int)(pos_y - 0.8) / SIZE][(int)(pos_x - 0.8)
			/ SIZE] == '1' ||
			mapa->final_map[(int)(pos_y - 0.8) / SIZE][(int)(pos_x + 0.8)
			/ SIZE] == '1')
		return (0);
	return (1);
}

void	move_cubed(t_map *mapa, double cos_angle, double sin_angle)
{
	if (mapa->key_w)
	{
		mapa->new_x += cos_angle * mapa->speed;
		mapa->new_y += sin_angle * mapa->speed;
	}
	if (mapa->key_s)
	{
		mapa->new_x -= cos_angle * mapa->speed;
		mapa->new_y -= sin_angle * mapa->speed;
	}
	if (mapa->key_a)
	{
		mapa->new_x += sin_angle * mapa->speed;
		mapa->new_y -= cos_angle * mapa->speed;
	}
	if (mapa->key_d)
	{
		mapa->new_x -= sin_angle * mapa->speed;
		mapa->new_y += cos_angle * mapa->speed;
	}
	if (is_wall(mapa, mapa->new_x, mapa->new_y))
	{
		mapa->xx = mapa->new_x;
		mapa->yy = mapa->new_y;
	}
}

void	rotate_cubed(t_map *mapa)
{
	if (mapa->key_left)
		mapa->starting_angle -= 0.05;
	if (mapa->key_right)
		mapa->starting_angle += 0.05;
}

void	set_player_dir_and_plane(t_map *mapa)
{
	mapa->dir_x = cos(mapa->starting_angle);
	mapa->dir_y = sin(mapa->starting_angle);
	mapa->plane_x = -mapa->dir_y * 0.66;
	mapa->plane_y = mapa->dir_x * 0.66;
}

int	cubed_render(t_map *mapa)
{
	mapa->new_x = mapa->xx;
	mapa->new_y = mapa->yy;
	move_cubed(mapa, mapa->dir_x, mapa->dir_y);
	rotate_cubed (mapa);
	mapa->map_x = mapa->xx;
	mapa->map_y = mapa->yy;
	if (mapa->starting_angle > 2 * PI)
		mapa->starting_angle = 0;
	if (mapa->starting_angle < 0)
		mapa->starting_angle = 2 * PI;
	set_player_dir_and_plane(mapa);
	clear_image(mapa);
	raycasting (mapa, -1);
	mlx_put_image_to_window(mapa->mlx_ptr, mapa->win_ptr, mapa->img_ptr, 0, 0);
	return (0);
}
