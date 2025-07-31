/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:38:04 by nkrasimi          #+#    #+#             */
/*   Updated: 2025/07/22 20:14:27 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

void load_texture(t_cube *cubed, t_texture *tex, char *path)
{
    tex->img_ptr = mlx_xpm_file_to_image(cubed->mlx, path, &tex->width, &tex->height);
    if (!tex->img_ptr)
    {
        perror("Error cargando textura");
        exit(1);
    }
    tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len, &tex->endian);
}

void load_all_textures(t_cube *cubed, t_map *mapa)
{
    load_texture(cubed, &cubed->tex_north, mapa->northtexture);
    load_texture(cubed, &cubed->tex_south, mapa->southtexture);
    load_texture(cubed, &cubed->tex_east,  mapa->easttexture);
    load_texture(cubed, &cubed->tex_west,  mapa->westtexture);
    /*load_texture(cubed, &cubed->tex_north, "eagle.xpm");
    load_texture(cubed, &cubed->tex_south, "greystone.xpm");
    load_texture(cubed, &cubed->tex_east,  "doom.xpm");
    load_texture(cubed, &cubed->tex_west,  "purplestone.xpm");
    load_texture(cubed, &cubed->tex_north, "iker.xpm");
    load_texture(cubed, &cubed->tex_south, "blen_textura.xpm");
    load_texture(cubed, &cubed->tex_east,  "gang.xpm");
    load_texture(cubed, &cubed->tex_west,  "texture_ton.xpm");*/
}

void	cubed_init(t_cube *cubed, t_map mapa)
{
	cubed->map = mapa.final_map;
	cubed->x = mapa.y * SIZE + (SIZE / 2);
	cubed->y = mapa.x * SIZE + (SIZE / 2);
	cubed->speed = 1;
	cubed->key_a = 0;
	cubed->key_w = 0;
	cubed->key_d = 0;
	cubed->key_s = 0;
    cubed->key_left = 0;
    cubed->key_right = 0;
	cubed->angle = mapa.starting_angle;
    set_player_dir_and_plane(cubed);
	cubed->floor_color = parse_color(mapa.floorcolor);
	cubed->ceiling_color = parse_color(mapa.ceilingcolor);
	cubed->mlx = mlx_init();
    load_all_textures(cubed, &mapa);
	cubed->win  = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3d");
	cubed->img_ptr = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->pixel_ptr = mlx_get_data_addr(cubed->img_ptr, &cubed->bpp, &cubed->line_length, &cubed->endian);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	init_values(t_map *mapa)
{
	mapa->northtexture = NULL;
	mapa->southtexture = NULL;
	mapa->easttexture = NULL;
	mapa->westtexture = NULL;
	mapa->path = NULL;
	mapa->name = NULL;
	mapa->floorcolor = NULL;
	mapa->ceilingcolor = NULL;
	mapa->toflood_map = NULL;
	mapa->final_map = NULL;
}

int	main(int ac, char **av)
{
	t_map	mapa;
	t_cube	cubed;

	if (ac != 2)
		return (msg(1, ARGERROR), 1);
	if (av[1][0] == '\0')
		return (msg(1, ARGERROR2), 1);
	init_values(&mapa);
	/* Vamos a ver Ibon aqui tenemos que hacer el parseo de los argumentos por terminal */
	/* Leer el mapa y comprobar que todo esta bien con el floodfill */
	if (ismap(av[1], &mapa) == 1)
	{
		mapa.path = ft_strdup(av[1]);
		printf("-> %s", mapa.path);
		if (check3atributtes(&mapa) == 0)
			return (msg(2, "Saliendo...\n"), freeall(&mapa), 1);
	}
	else
		return (msg(1, ARGERROR3), 1);
	cubed_init(&cubed, mapa);
	mlx_hook(cubed.win, 2, 1L<<0, key_press, &cubed, &mapa);
    mlx_hook(cubed.win, 3, 1L<<1, key_release, &cubed);
    mlx_hook(cubed.win, DestroyNotify, StructureNotifyMask,
		close_handler, &cubed, &mapa);
	mlx_loop_hook(cubed.mlx, cubed_render, &cubed);
	mlx_loop(cubed.mlx);
	freeall(&mapa);
	return (0);
}
