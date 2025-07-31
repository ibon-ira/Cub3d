/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:25:13 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 20:08:42 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

char	*noendl_dup(const char *s1)
{
	size_t		i;
	char		*memory;

	i = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
		i++;
	memory = ft_calloc(i + 1, sizeof(char));
	if (!memory)
		return (0);
	i = 0;
	while (s1[i] != '\n' && s1[i] != '\0')
	{
		memory[i] = s1[i];
		i++;
	}
	return (memory);
}

void	mapcpy(t_map *map, int *i, int fd)
{
	int		ii;
	char	*line;
	int		x;

	x = 0;
	printf("valor i: %d\n", *i);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n"))
		{
			ii = 0;
			while (line[ii])
			{
				map->map[x][ii] = line[ii];
				ii++;
			}
			map->map[x][ii] = '\0';
			(x)++;
		}
		ft_memdel(line);
	}
	map->row = x;
}

void	getfinalmap(t_map *map)
{
	int	i;

	i = 0;
	map->final_map = ft_calloc(map->row + 1, sizeof(char *));
	if (!map->final_map)
		return (msg(2, MEMERROR), exit(1));
	while (i < map->row)
	{
		map->final_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	i = 0;
	while (map->final_map[i])
	{
		msg(1, map->final_map[i]);
		i++;
	}
}

void	flood_staff(t_map *map)
{
	int	i;

	i = 0;
	map4flood(map);
	if (map->toflood_map == NULL)
		return (msg(2, "Error\n"), freeall(map), exit(1));
	if (checkns(map, 0, 0, 0) != 1)
		return (msg(2, SPOTERROR), freeall(map), exit(1));
	flood_fill(map, map->toflood_map, map->x, map->y);
	while (map->toflood_map[i])
	{
		msg(1, map->toflood_map[i]);
		i++;
	}
}
