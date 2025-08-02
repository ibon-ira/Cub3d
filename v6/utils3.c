/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:30:31 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 19:29:42 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	map4flood(t_map *map)
{
	int	i;

	i = 0;
	msg(2, "Let's start the map to flood it\n");
	map->toflood_map = ft_calloc((map->row) + 1, sizeof(char *));
	if (!map->toflood_map)
		return (msg(2, MEMERROR), exit(1));
	while (i < map->row)
	{
		map->toflood_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	i = 0;
	while (map->toflood_map[i])
	{
		msg(1, map->toflood_map[i]);
		i++;
	}
}

int	checkns(t_map *map, int count, int i, int ii)
{
	while (map->toflood_map[i])
	{
		ii = 0;
		while (map->toflood_map[i][ii])
		{
			if (ft_is_nswe(map->toflood_map[i][ii]) != 1)
				return (0);
			if (map->toflood_map[i][ii] == 'N' || map->toflood_map[i][ii] == 'S'
				|| map->toflood_map[i][ii] == 'E'
				|| map->toflood_map[i][ii] == 'W')
			{
				if (count == 0)
					add_values(map, i, ii);
				know_starting_angle(map, i, ii);
				count++;
			}
			ii++;
		}
		i++;
	}
	return (count);
}

void	add_values(t_map *map, int i, int ii)
{
	map->x = i;
	map->y = ii;
}

void	msg(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}
