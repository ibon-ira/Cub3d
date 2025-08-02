/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:18:58 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:16:26 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	perform_dda(t_map *mapa, double *side_dist_x, double *side_dist_y)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += mapa->delta_dist_x;
			mapa->map_x += mapa->step_x;
			mapa->side = 0;
		}
		else
		{
			*side_dist_y += mapa->delta_dist_y;
			mapa->map_y += mapa->step_y;
			mapa->side = 1;
		}
		if (mapa->final_map[mapa->map_y / SIZE][mapa->map_x / SIZE] == '1')
			hit = 1;
	}
	return (mapa->side);
}

void	init_dda(t_map *mapa, double *side_dist_x, double *side_dist_y)
{
	mapa->map_x = (int)(mapa->xx);
	mapa->map_y = (int)(mapa->yy);
	mapa->delta_dist_x = fabs(1 / mapa->ray_dir_x);
	mapa->delta_dist_y = fabs(1 / mapa->ray_dir_y);
	if (mapa->ray_dir_x < 0)
	{
		mapa->step_x = -1;
		*side_dist_x = (mapa->xx - mapa->map_x) * mapa->delta_dist_x;
	}
	else
	{
		mapa->step_x = 1;
		*side_dist_x = (mapa->map_x + 1.0 - mapa->xx) * mapa->delta_dist_x;
	}
	if (mapa->ray_dir_y < 0)
	{
		mapa->step_y = -1;
		*side_dist_y = (mapa->yy - mapa->map_y) * mapa->delta_dist_y;
	}
	else
	{
		mapa->step_y = 1;
		*side_dist_y = (mapa->map_y + 1.0 - mapa->yy) * mapa->delta_dist_y;
	}
}

void	calculate_wall_data(t_map *mapa, double *dist)
{
	if (mapa->side == 0)
		*dist = (mapa->map_x - mapa->xx + (1 - mapa->step_x) / 2)
			/ mapa->ray_dir_x / SIZE;
	else
		*dist = (mapa->map_y - mapa->yy + (1 - mapa->step_y) / 2)
			/ mapa->ray_dir_y / SIZE;
	mapa->line_height = (int)(HEIGHT / *dist);
	if (mapa->side == 0)
		mapa->wall_x = mapa->yy / SIZE + *dist * mapa->ray_dir_y;
	else
		mapa->wall_x = mapa->xx / SIZE + *dist * mapa->ray_dir_x;
	mapa->wall_x -= floor(mapa->wall_x);
}

void	select_texture(t_map *mapa)
{
	if (mapa->side == 0)
	{
		if (mapa->ray_dir_x > 0)
			mapa->current_tex = &mapa->tex_east;
		else
			mapa->current_tex = &mapa->tex_west;
	}
	else
	{
		if (mapa->ray_dir_y > 0)
			mapa->current_tex = &mapa->tex_south;
		else
			mapa->current_tex = &mapa->tex_north;
	}
}

void	raycasting(t_map *mapa, int i)
{
	double	camera_x;
	double	side_x;
	double	side_y;
	double	dist;
	int		start_y;

	while (++i < WIDTH)
	{
		camera_x = 2 * i / (double)WIDTH - 1;
		mapa->ray_dir_x = mapa->dir_x + mapa->plane_x * camera_x;
		mapa->ray_dir_y = mapa->dir_y + mapa->plane_y * camera_x;
		init_dda(mapa, &side_x, &side_y);
		perform_dda(mapa, &side_x, &side_y);
		calculate_wall_data(mapa, &dist);
		select_texture(mapa);
		start_y = (HEIGHT - mapa->line_height) / 2;
		mapa->end = start_y + mapa->line_height;
		if (start_y < 0)
			start_y = 0;
		if (mapa->end > HEIGHT)
			mapa->end = HEIGHT;
		draw_3d_dda(i, start_y, mapa->end, mapa);
	}
}
