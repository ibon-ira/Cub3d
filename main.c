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

float fixed_dist(float x1, float y1, float x2, float y2, t_cube *cubed)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - cubed->angle;
    float fix_dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle);
    return fix_dist;
}

void cast_rays_minimap(t_cube *cubed, int i)
{
    float   ray_angle;
    float   delta_angle;
    float   ray_dx;
    float   ray_dy;

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
}

void    draw_3d (int i, int start_y, int end, t_cube *cubed)
{
    int y = 0;
    while (y < start_y)
    {
        put_pixel(i, y, 0x0000FF, cubed);
        y++;
    }
    while (y < end && y < HEIGHT)
    {
        put_pixel(i, y, 0xAAAAAA, cubed);
        y++;
    }
    while (y < HEIGHT)
    {
        put_pixel(i, y, 0x00FF00, cubed);
        y++;
    }
}

void raycasting(t_cube *cubed, int i)
{
    float   ray_angle;
    float   delta_angle;
    float   ray_dx;
    float   ray_dy;

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
        float dist = fixed_dist(cubed->x, cubed->y, cubed->ray_x, cubed->ray_y, cubed);
        float height = (SIZE / dist) * ((WIDTH / 2) / tan(POV / 2));
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;
        draw_3d (i, start_y, end, cubed);
        ray_angle += delta_angle;
    }
}

int is_wall(t_cube *cubed, int pos_x, int pos_y)
{
    if (cubed->map[pos_y / SIZE][pos_x / SIZE] == '1')
        return (0);
    return (1);
}

void move_cubed(t_cube *cubed, float cos_angle, float sin_angle)
{
	if (cubed->key_w)
    {
        cubed->new_x += cos_angle * cubed->speed;
        cubed->new_y += sin_angle * cubed->speed;
    }
    if (cubed->key_s)
    {
        cubed->new_x -= cos_angle * cubed->speed;
        cubed->new_y -= sin_angle * cubed->speed;
    }
    if (cubed->key_a)
    {
        cubed->new_x += sin_angle * cubed->speed;
        cubed->new_y -= cos_angle * cubed->speed;
    }
    if (cubed->key_d)
    {
        cubed->new_x -= sin_angle * cubed->speed;
        cubed->new_y += cos_angle * cubed->speed;
    }
    if (is_wall(cubed, cubed->new_x, cubed->new_y))
        cubed->x = cubed->new_x;
    if (is_wall(cubed, cubed->new_x, cubed->new_y))
        cubed->y = cubed->new_y;
}

void    rotate_cubed (t_cube *cubed)
{
    if (cubed->key_left)
        cubed->angle -= 0.05;
    if (cubed->key_right)
        cubed->angle += 0.05;
}

void set_player_dir_and_plane(t_cube *cubed)
{
    float plane_length;

    cubed->dir_x = cos(cubed->angle);
    cubed->dir_y = sin(cubed->angle);
    plane_length = tan(POV / 2); // POV en radianes
    cubed->plane_x = -cubed->dir_y * plane_length;
    cubed->plane_y = cubed->dir_x * plane_length;
}

int cubed_render(t_cube *cubed)
{
    float   cos_angle;
    float   sin_angle;

//    cubed->dir_y = sin(cubed->angle);
//    cubed->dir_x = cos(cubed->angle);
    cubed->new_x = cubed->x;
    cubed->new_y = cubed->y;
    set_player_dir_and_plane(cubed);
	move_cubed(cubed, cubed->dir_x, cubed->dir_y);
    rotate_cubed (cubed);
    if (cubed->angle > 2 * PI)
    cubed->angle = 0;
    if (cubed->angle < 0)
    cubed->angle = 2 * PI;
    clear_image(cubed);
    raycasting (cubed, -1);
    draw_map(cubed);
    //put_circle(MINIMAP_X * SIZE, MINIMAP_Y * SIZE, 5, 0x00FF00, cubed);
    put_circle(cubed->x, cubed->y, 5, 0x00FF00, cubed);
    cast_rays_minimap(cubed, -1);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
    return (0);
}

void	cubed_init(t_cube *cubed)
{
	cubed->map = get_map();
	cubed->x = 100;
	cubed->y = 110;
	cubed->speed = 1;
	cubed->key_a = 0;
	cubed->key_w = 0;
	cubed->key_d = 0;
	cubed->key_s = 0;
    cubed->key_left = 0;
    cubed->key_right = 0;
//	cubed->angle = get_angle();
	cubed->angle = PI/2;
	cubed->mlx = mlx_init();
//    cubed->wall_texture = mlx_xpm_file_to_image(cubed->mlx, "doom.xpm", &cubed->tex_width, &cubed->tex_height);
//    cubed->tex_data = mlx_get_data_addr(cubed->wall_texture_N, &cubed->tex_bpp, &cubed->tex_line_length, &cubed->tex_endian);
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
