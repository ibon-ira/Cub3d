/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parselineutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:53:10 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 20:12:14 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	check_array_for_atributes(t_map *map, char **arr)
{
	if (ft_strcmp(arr[0], "NO") && ft_strcmp(arr[0], "SO")
		&& ft_strcmp(arr[0], "WE") && ft_strcmp(arr[0], "EA")
		&& ft_strcmp(arr[0], "F") && ft_strcmp(arr[0], "C"))
		return (msg(2, arr[0]), msg(2, MAPERROR10), 1);
	if (!ft_strcmp(arr[0], "F") || !ft_strcmp(arr[0], "C"))
	{
		if (asign_colors(map, arr))
			return (1);
	}
	else
	{
		if (asign_directions(map, arr))
			return (1);
	}
	return (0);
}

static void	checkatributes(t_map *map, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(line, ' ');
	if (!arr)
		return (msg(2, MAPERROR9), ft_memdel(line), freeall(map), exit(1));
	while (arr[i])
		i++;
	if (i > 2 && ft_strcmp(arr[2], "\n"))
		return (msg(2, MAPERROR9), printf("%s", arr[2]), ft_memdel(line),
			freeall(map), freeme(arr), exit(1));
	if (!ft_strcmp(arr[0], "\n"))
		return (freeme(arr));
	if (check_array_for_atributes(map, arr))
		return (freeme(arr), ft_memdel(line), freeall(map), exit(1));
	freeme(arr);
}

static int	all_atributes_asigned(t_map *map)
{
	if (map->northtexture && map->southtexture && map->easttexture
		&& map->westtexture && map->floorcolor && map->ceilingcolor)
		return (1);
	else
		return (0);
}

void	parsefloorceilingdirections(t_map *map, int i, int fd)
{
	char	*line;

	while (i)
	{
		line = get_next_line(fd);
		if (i == 1 && line == NULL)
			return (msg(2, MAPERROR3), freetextures(map), exit(1));
		if (line && ft_strcmp(line, "\n"))
			checkatributes(map, line);
		if (all_atributes_asigned(map))
			return (ft_memdel(line));
		if (line == NULL)
			break ;
		ft_memdel(line);
		i++;
	}
}
