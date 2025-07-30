#include "cub3d.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "100000001000001";
    map[2] = "100000100010101";
    map[3] = "110110101111101";
    map[4] = "100000100010001";
    map[5] = "101110101000101";
    map[6] = "101001000100101";
    map[7] = "101000110100011";
    map[8] = "100010000001001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

/*void cast_rays_minimap(t_cube *cubed, int i)
{
    double   ray_angle;
    double   delta_angle;
    double   ray_dx;
    double   ray_dy;

    ray_angle = cubed->angle - (POV / 2);
    delta_angle = POV / WIDTH;
    while (++i < WIDTH)
    {
        cubed->ray_x = cubed->x;
        cubed->ray_y = cubed->y;
        ray_dx = cos(ray_angle);
        ray_dy = sin(ray_angle);

        while (1)
        {
            cubed->ray_x += ray_dx;
            cubed->ray_y += ray_dy;
            if (cubed->map[(int)(cubed->ray_y / SIZE)][(int)(cubed->ray_x / SIZE)] == '1')
                break;
        }
        draw_line_on_map(cubed->x, cubed->y, cubed->ray_x, cubed->ray_y, cubed);
        ray_angle += delta_angle;
    }
}*/

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

void load_all_textures(t_cube *cubed)
{
    /*load_texture(cubed, &cubed->tex_north, "doom.xpm");
    load_texture(cubed, &cubed->tex_south, "doom2.xpm");
    load_texture(cubed, &cubed->tex_east,  "doom3.xpm");
    load_texture(cubed, &cubed->tex_west,  "doom4.xpm");
    load_texture(cubed, &cubed->tex_north, "eagle.xpm");
    load_texture(cubed, &cubed->tex_south, "greystone.xpm");
    load_texture(cubed, &cubed->tex_east,  "doom.xpm");
    load_texture(cubed, &cubed->tex_west,  "purplestone.xpm");*/
    load_texture(cubed, &cubed->tex_north, "iker.xpm");
    load_texture(cubed, &cubed->tex_south, "blen_textura.xpm");
    load_texture(cubed, &cubed->tex_east,  "gang.xpm");
    load_texture(cubed, &cubed->tex_west,  "texture_ton.xpm");
}

void	cubed_init(t_cube *cubed)
{
	cubed->map = get_map();
	cubed->x = 60;
	cubed->y = 60;
    //cubed->map_x = 4;
    //cubed->map_y = 4;
	cubed->speed = 2;
	cubed->key_a = 0;
	cubed->key_w = 0;
	cubed->key_d = 0;
	cubed->key_s = 0;
    cubed->key_left = 0;
    cubed->key_right = 0;
//	cubed->angle = get_angle();
	cubed->angle = 0;
    set_player_dir_and_plane(cubed);
	cubed->mlx = mlx_init();
    load_all_textures(cubed);
	cubed->win  = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3d");
	cubed->img_ptr = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->pixel_ptr = mlx_get_data_addr(cubed->img_ptr, &cubed->bpp, &cubed->line_length, &cubed->endian);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
}

int	main(void)
{
	t_cube	cubed;

    cubed_init(&cubed);
	mlx_hook(cubed.win, 2, 1L<<0, key_press, &cubed);
    mlx_hook(cubed.win, 3, 1L<<1, key_release, &cubed);
    mlx_hook(cubed.win, DestroyNotify, StructureNotifyMask,
		close_handler, &cubed);
	mlx_loop_hook(cubed.mlx, cubed_render, &cubed);
	mlx_loop(cubed.mlx);
	return (0);
}
