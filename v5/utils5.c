/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:11:19 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 20:11:02 by iksaiz-m         ###   ########.fr       */
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
		map->starting_angle = 0;
	else if (map->toflood_map[i][ii] == 'W')
		map->starting_angle = PI;
	printf("character: %c\n", map->toflood_map[i][ii]);
	printf("starting angle: %f\n", map->starting_angle);
}
