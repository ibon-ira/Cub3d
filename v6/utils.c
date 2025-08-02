/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:47:48 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:00:31 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

int	ismap(char *str, t_map *map)
{
	int		i;
	int		ii;
	char	*check;

	i = ft_strlen(str);
	ii = checkmap_name_folders(str);
	if (ii > 0)
		ii++;
	if (i - ii < 5)
		return (msg(2, FORMAT), exit(1), 0);
	check = &str[i - 4];
	check_printable_map_name(str, i, ii);
	if (check[0] == '.' && check[1] == 'c' && check[2] == 'u'
		&& check[3] == 'b' && check[4] == '\0')
	{
		map->name = ft_substr(str, ii, i -4 - ii);
		return (1);
	}
	return (0);
}

int	check3atributtes(t_map *map)
{
	int	fd;
	int	i;

	fd = open(map->path, O_RDONLY);
	if (fd > 0)
	{
		msg(1, "Todo el parseo funciona correctamente\n");
		i = 1;
		parsefloorceilingdirections(map, i, fd);
		i = 0;
		i = 0;
		mapcpy(map, &i, fd);
		printf("El numero de lineas del mapa es: %d\n", map->row);
		getfinalmap(map);
		if (map->final_map == NULL)
			return (msg(2, MAPERROR), freeme(map->final_map), 0);
		flood_staff(map);
	}
	else
		return (msg(2, MAPERROR2), 0);
	return (close(fd), 1);
}
