/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:55:39 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:05:34 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	parse_color(const char *line)
{
	int	r;
	int	g;
	int	b;

	while (*line && (*line == 'F' || *line == ' '))
		line++;
	r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	b = ft_atoi(line);
	return ((r << 16) | (g << 8) | b);
}

// int	key_press(int keysym, t_map *mapa)
// {
// 	if (keysym == XK_Escape)
// 		closewindow(mapa);
// 	if (keysym == XK_a)
// 		mapa->key_a = 1;
// 	else if (keysym == XK_d)
// 		mapa->key_d = 1;
// 	else if (keysym == XK_w)
// 		mapa->key_w = 1;
// 	else if (keysym == XK_s)
// 		mapa->key_s = 1;
// 	else if (keysym == XK_Left)
// 		mapa->key_left = 1;
// 	else if (keysym == XK_Right)
// 		mapa->key_right = 1;
// 	return (0);
// }

int	key_release(int keysym, t_map *mapa)
{
	if (keysym == XK_a)
		mapa->key_a = 0;
	else if (keysym == XK_d)
		mapa->key_d = 0;
	else if (keysym == XK_w)
		mapa->key_w = 0;
	else if (keysym == XK_s)
		mapa->key_s = 0;
	else if (keysym == XK_Left)
		mapa->key_left = 0;
	else if (keysym == XK_Right)
		mapa->key_right = 0;
	return (0);
}
