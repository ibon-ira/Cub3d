/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asignatributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:57:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 20:01:07 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

static int	fill_colors(t_map *map, char *noendline, char *arr0)
{
	if (!ft_strcmp(arr0, "F") && !map->floorcolor)
	{
		msg(1, "floor\n");
		return (map->floorcolor = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "C") && !map->ceilingcolor)
	{
		msg(1, "ceiling\n");
		return (map->ceilingcolor = ft_strdup(noendline), 0);
	}
	return (msg(2, MAP_ARG_DUP), 1);
}

static int	fill_directions(t_map *map, char *noendline, char *arr0)
{
	if (!ft_strcmp(arr0, "NO") && !map->northtexture)
	{
		msg(1, "north\n");
		return (map->northtexture = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "SO") && !map->southtexture)
	{
		msg(1, "south\n");
		return (map->southtexture = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "WE") && !map->westtexture)
	{
		msg(1, "west\n");
		return (map->westtexture = ft_strdup(noendline), 0);
	}
	if (!ft_strcmp(arr0, "EA") && !map->easttexture)
	{
		msg(1, "east\n");
		return (map->easttexture = ft_strdup(noendline), 0);
	}
	return (msg(2, MAP_ARG_DUP), msg(2, arr0), msg(2, "\n"), 1);
}

int	asign_directions(t_map *map, char **arr)
{
	char	*noendline;
	int		fd;

	if (arr[1])
		noendline = noendl_dup(arr[1]);
	else
		return (msg(2, NOPATH), 1);
	if (noendline)
		if (fill_directions(map, noendline, arr[0]))
			return (ft_memdel(noendline), 1);
	fd = open(noendline, O_RDONLY);
	ft_memdel(noendline);
	if (fd > 0)
		close(fd);
	else
		return (msg(2, IMG), 1);
	return (0);
}

int	asign_colors(t_map *map, char **arr)
{
	char	*noendline;
	char	**arr2;

	if (arr[1])
		noendline = noendl_dup(arr[1]);
	else
		return (msg(2, NOPATH), 1);
	if (noendline)
		if (fill_colors(map, noendline, arr[0]))
			return (ft_memdel(noendline), 1);
	arr2 = ft_split(noendline, ',');
	if (!arr2)
		return (ft_memdel(noendline), 1);
	ft_memdel(noendline);
	if (isvalidnum(arr2))
		return (freeme(arr2), 1);
	freeme(arr2);
	return (0);
}
