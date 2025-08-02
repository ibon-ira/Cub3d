/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:53:31 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:00:55 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	isrgbable(char **arr2)
{
	int	i;

	i = 0;
	while (arr2[i])
	{
		if (ft_atoi(arr2[i]) < 0 || ft_atoi(arr2[i]) > 255)
			return (msg(2, RGBERROR2), 1);
		i++;
	}
	msg(1, "\nTodo esta funcionando muy bien por lo visto :)\n");
	return (0);
}

int	isvalidnum(char **arr2)
{
	int	i;
	int	ii;

	i = 0;
	while (arr2[i])
		i++;
	if (i != 3)
		return (msg(2, RGBERROR), 1);
	i = 0;
	while (arr2[i])
	{
		ii = 0;
		while (arr2[i][ii])
		{
			if (!ft_isdigit(arr2[i][ii]))
				return (msg(2, FORMAT3), 1);
			ii++;
		}
		i++;
	}
	if (isrgbable(arr2))
		return (1);
	return (0);
}

int	ft_is_nswe(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '1'
		|| c == '0' || c == ' ' || c == '	' || c == '\n')
		return (1);
	return (0);
}

void	flood_fill(t_map *mapa, char **map, int x, int y)
{
	if (map[x][y] == ' ' || map[x][y] == '\n' || map[x][y] == '	')
		return (msg(2, MAPERROR4), freeall(mapa), exit(1));
	if (map[x][y] && map[x][y] != '1')
	{
		if (map[x][y] != 1)
			map[x][y] = '1';
		flood_fill(mapa, map, x + 1, y);
		flood_fill(mapa, map, x - 1, y);
		flood_fill(mapa, map, x, y + 1);
		flood_fill(mapa, map, x, y - 1);
	}
}
