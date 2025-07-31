/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:47:48 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/07/22 20:07:13 by iksaiz-m         ###   ########.fr       */
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
	// Tenemos que importar el GNL para poder parsear esto correctamente bueno y la libft tambien
	if (fd > 0)
	{
		msg(1, "Todo el parseo funciona correctamente\n");
		/* Primero checkeo las 4 direcciones y las meto en un doble punter de la estructura */
		i = 1;
		parsefloorceilingdirections(map, i, fd);
		// directions_bridge(map, i, fd);
		/* Despues lo mismo con los colores del suelo y del cielo */
		i = 0;
		// floornceiling(map, i, fd);
		/* Para terminar meto las lineas de mapa y me aseguro de quitar espacios y ver que los caracteres son correctos REMINDER:El mapa que le tengo que pasar a Ibon es la version con espacios*/
		i = 0;
		mapcpy(map, &i, fd);
		printf("El numero de lineas del mapa es: %d\n", map->row);
		getfinalmap(map);
		if (map->final_map == NULL)
			return (msg(2, MAPERROR), freeme(map->final_map), 0);
		/* Floodfill para asegurarme que el mapa esta correctamente cerrado */
		flood_staff(map);
	}
	else
		return (msg(2, MAPERROR2), 0);
	return (close(fd), 1);
}
