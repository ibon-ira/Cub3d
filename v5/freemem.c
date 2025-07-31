/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:35:42 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 19:33:47 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void	ft_memdel(void *ptr)
{
	if (ptr != 0)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	freeme(char **memory)
{
	int	i;

	i = 0;
	if (!memory)
		return ;
	while (memory[i])
	{
		ft_memdel(memory[i]);
		i++;
	}
	ft_memdel(memory);
}

void	freetextures(t_map *map)
{
	ft_memdel(map->path);
	ft_memdel(map->name);
	ft_memdel(map->northtexture);
	ft_memdel(map->southtexture);
	ft_memdel(map->westtexture);
	ft_memdel(map->easttexture);
	ft_memdel(map->floorcolor);
	ft_memdel(map->ceilingcolor);
}

void	freeall(t_map *map)
{
	freetextures(map);
	freeme(map->toflood_map);
	freeme(map->final_map);
}
