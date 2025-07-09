#include "cub3d.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 11);
    map[0] = "111111111111111";
    map[1] = "1000N0000000001";
    map[2] = "100000000000001";
    map[3] = "100000100000001";
    map[4] = "100000000000001";
    map[5] = "100000010000001";
    map[6] = "100001000000001";
    map[7] = "100000000000001";
    map[8] = "100000000000001";
    map[9] = "111111111111111";
    map[10] = NULL;
    return (map);
}

void move_cubed(t_cube *cubed)
{
    float cos_angle = cos(cubed->angle);
    float sin_angle = sin(cubed->angle);

    if (cubed->angle > 2 * PI)
        cubed->angle = 0;
    if (cubed->angle < 0)
        cubed->angle = 2 * PI;
	if (cubed->key_s)
    {
        cubed->x += cos_angle * cubed->speed;
        cubed->y += sin_angle * cubed->speed;
    }
    if (cubed->key_w)
    {
        cubed->x -= cos_angle * cubed->speed;
        cubed->y -= sin_angle * cubed->speed;
    }
    if (cubed->key_d)
    {
        cubed->x += sin_angle * cubed->speed;
        cubed->y -= cos_angle * cubed->speed;
    }
    if (cubed->key_a)
    {
        cubed->x -= sin_angle * cubed->speed;
        cubed->y += cos_angle * cubed->speed;
    }
}

int cubed_render(t_cube *cubed)
{
	move_cubed(cubed);
    clear_image(cubed);
    draw_map(cubed);
	put_circle(cubed->x, cubed->y, 5, 0x00008B, cubed);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
    return 0;
}

void	cubed_init(t_cube *cubed)
{
	cubed->map = get_map();
	cubed->x = 100;
	cubed->y = 110;
	cubed->speed = 5;
	cubed->key_a = 0;
	cubed->key_w = 0;
	cubed->key_d = 0;
	cubed->key_s = 0;
//	cubed->angle = get_angle();
	cubed->angle = PI/2;
	cubed->mlx = mlx_init();
	cubed->win  = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3d");
	cubed->img_ptr = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
	cubed->pixel_ptr = mlx_get_data_addr(cubed->img_ptr, &cubed->bpp, &cubed->line_length, &cubed->endian);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
}

int	main(void)
{
	t_cube	cubed;

	cubed_init(&cubed);
//	put_pixel(cubed.x, cubed.y, 0xFFFFFF, &cubed);
//	put_cubed(cubed.x, cubed.y, 0x00FF00, &cubed);
	//put_circle(cubed.x, cubed.y, 5, 0x00FF00, &cubed);
	//draw_map(&cubed);
//	put_circle(cubed.x, cubed.y, 5, 0x00FF00, &cubed);
	//mlx_hook(cubed.win, KeyPress, KeyPressMask, key_handler, &cubed);
	mlx_hook(cubed.win, 2, 1L<<0, key_press, &cubed);
    mlx_hook(cubed.win, 3, 1L<<1, key_release, &cubed);
	mlx_loop_hook(cubed.mlx, cubed_render, &cubed);
	mlx_loop(cubed.mlx);
	return (0);
}
