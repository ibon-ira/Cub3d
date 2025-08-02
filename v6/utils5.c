/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:11:19 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:01:04 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	closewindow(t_map *mapa)
{
	mlx_destroy_image(mapa->mlx_ptr, mapa->img_ptr);
	mlx_destroy_image(mapa->mlx_ptr, mapa->tex_north.img_ptr);
	mlx_destroy_image(mapa->mlx_ptr, mapa->tex_south.img_ptr);
	mlx_destroy_image(mapa->mlx_ptr, mapa->tex_east.img_ptr);
	mlx_destroy_image(mapa->mlx_ptr, mapa->tex_west.img_ptr);
	mlx_destroy_window(mapa->mlx_ptr, mapa->win_ptr);
	mlx_destroy_display(mapa->mlx_ptr);
	freeall(mapa);
	free(mapa->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keysym, t_map *mapa)
{
	if (keysym == XK_Escape)
		closewindow(mapa);
	if (keysym == XK_a)
		mapa->key_a = 1;
	else if (keysym == XK_d)
		mapa->key_d = 1;
	else if (keysym == XK_w)
		mapa->key_w = 1;
	else if (keysym == XK_s)
		mapa->key_s = 1;
	else if (keysym == XK_Left)
		mapa->key_left = 1;
	else if (keysym == XK_Right)
		mapa->key_right = 1;
	return (0);
}

int	checkmap_name_folders(char *str)
{
	int	i;
	int	ii;

	i = 0;
	ii = 0;
	while (str[i])
	{
		if (str[i] == '/')
			ii = i;
		i++;
	}
	return (ii);
}

int	check_printable_map_name(char *str, int i, int ii)
{
	while (ii < i - 4)
	{
		if (!ft_isprint(str[ii]))
			return (msg(2, FORMAT2), exit(1), 0);
		ii++;
	}
	return (1);
}

void	know_starting_angle(t_map *map, int i, int ii)
{
	if (map->toflood_map[i][ii] == 'S')
		map->starting_angle = PI / 2;
	else if (map->toflood_map[i][ii] == 'N')
		map->starting_angle = 3 * PI / 2;
	else if (map->toflood_map[i][ii] == 'E')
		map->starting_angle = 2 * PI;
	else if (map->toflood_map[i][ii] == 'W')
		map->starting_angle = PI;
	printf("character: %c\n", map->toflood_map[i][ii]);
	printf("starting angle: %f\n", map->starting_angle);
}
