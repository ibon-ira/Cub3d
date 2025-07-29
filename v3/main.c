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

void cast_rays_minimap(t_cube *cubed, int i)
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
}

int	perform_dda(t_cube *cubed, double *side_dist_x, double *side_dist_y)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += cubed->delta_dist_x;
			cubed->map_x += cubed->step_x;
			cubed->side = 0;
		}
		else
		{
			*side_dist_y += cubed->delta_dist_y;
			cubed->map_y += cubed->step_y;
			cubed->side = 1;
		}
		if (cubed->map[cubed->map_y / SIZE][cubed->map_x / SIZE] == '1')
			hit = 1;
	}
	return (cubed->side);
}

void    init_dda(t_cube *cubed, double *side_dist_x, double *side_dist_y)
{
        cubed->map_x = (int)(cubed->x);
        cubed->map_y = (int)(cubed->y);
        cubed->delta_dist_x = fabs(1 / cubed->ray_dir_x);
        cubed->delta_dist_y = fabs(1 / cubed->ray_dir_y);

        if (cubed->ray_dir_x < 0)
        {
            cubed->step_x = -1;
            *side_dist_x = (cubed->x - cubed->map_x) * cubed->delta_dist_x;
        }
        else
        {
            cubed->step_x = 1;
            *side_dist_x = (cubed->map_x + 1.0 - cubed->x) * cubed->delta_dist_x;
        }
        if (cubed->ray_dir_y < 0)
        {
            cubed->step_y = -1;
            *side_dist_y = (cubed->y - cubed->map_y) * cubed->delta_dist_y;
        }
        else
        {
            cubed->step_y = 1;
            *side_dist_y = (cubed->map_y + 1.0 - cubed->y) * cubed->delta_dist_y;
        }
}

void	calculate_wall_data(t_cube *cubed, double *dist, double *wall_x)
{
	if (cubed->side == 0)
		*dist = (cubed->map_x - cubed->x + (1 - cubed->step_x) / 2)
			/ cubed->ray_dir_x / SIZE;
	else
		*dist = (cubed->map_y - cubed->y + (1 - cubed->step_y) / 2)
			/ cubed->ray_dir_y / SIZE;
	cubed->line_height = (int)(HEIGHT / *dist);
    if (cubed->side == 0)
	    cubed->wall_x = cubed->y / SIZE + *dist * cubed->ray_dir_y;
    else
	    cubed->wall_x = cubed->x / SIZE + *dist * cubed->ray_dir_x;
    cubed->wall_x -= floor(cubed->wall_x);
}

void    draw_wall(int x, int start_y, int end_y, t_cube *cubed)
{
    double wall_x;
    int tex_x;
    int d;
    int tex_y;
    int offset;
    int color;

    t_texture *tex = cubed->current_tex;
    wall_x = cubed->wall_x - floor(cubed->wall_x);
    tex_x = (int)(wall_x * tex->width);
    if ((cubed->side == 0 && cubed->ray_dir_x > 0) || 
        (cubed->side == 1 && cubed->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;
    while (start_y < end_y)
        for (int y = start_y; y < end_y; y++)
    {
        d = y * 256 - HEIGHT * 128 + cubed->line_height * 128;
        tex_y = (d * tex->height) / cubed->line_height / 256;

        offset = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
        color = *(int *)(tex->data + offset);

        put_pixel(x, y, color, cubed);
        start_y++;
    }
}

void draw_3d_dda(int x, int start_y, int end_y, t_cube *cubed)
{
    int y;

    y = -1;
    while (++y < start_y)
        put_pixel(x, y, 0x87CEEB, cubed);
    draw_wall (x, start_y, end_y, cubed);
    y = end_y;
    while (y < HEIGHT)
    {
        put_pixel(x, y, 0x444444, cubed);
        y++; 
    }
}

void select_texture(t_cube *cubed)
{
    if (cubed->side == 0)
    {
        if (cubed->ray_dir_x > 0)
            cubed->current_tex = &cubed->tex_west;
        else
            cubed->current_tex = &cubed->tex_east;
    }
    else
    {
        if (cubed->ray_dir_y > 0)
            cubed->current_tex = &cubed->tex_north;
        else
            cubed->current_tex = &cubed->tex_south;
    }
}

void    raycasting(t_cube *cubed, int i)
{
	double	camera_x;
	double	side_x;
	double	side_y;
	double	wall_x;
	double	dist;
    int     start_y;
    int     end;
	while (++i < WIDTH)
	{
		camera_x = 2 * i / (double)WIDTH - 1;
	    cubed->ray_dir_x = cubed->dir_x + cubed->plane_x * camera_x;
	    cubed->ray_dir_y = cubed->dir_y + cubed->plane_y * camera_x;
	    init_dda(cubed, &side_x, &side_y);
	    perform_dda(cubed, &side_x, &side_y);
	    calculate_wall_data(cubed, &dist, &wall_x);
	    select_texture(cubed);
        start_y = (HEIGHT - cubed->line_height) / 2;
        end = start_y + cubed->line_height;
        if (start_y < 0)
	        start_y = 0;
        if (end > HEIGHT)
	        end = HEIGHT;
        draw_3d_dda(i, start_y, end, cubed);
	}
}

int is_wall(t_cube *cubed, double pos_x, double pos_y)
{
    if (cubed->map[(int)(pos_y + 0.8) / SIZE][(int)(pos_x + 0.8) / SIZE] == '1' ||
            cubed->map[(int)(pos_y + 0.8) / SIZE][(int)(pos_x - 0.8) / SIZE] == '1' ||
            cubed->map[(int)(pos_y - 0.8) / SIZE][(int)(pos_x - 0.8) / SIZE] == '1' ||
            cubed->map[(int)(pos_y - 0.8) / SIZE][(int)(pos_x + 0.8) / SIZE] == '1')
            return (0);
    return (1);
}

void move_cubed(t_cube *cubed, double cos_angle, double sin_angle)
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
    {
        cubed->x = cubed->new_x;
        cubed->y = cubed->new_y;
    }
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
    cubed->dir_x = cos(cubed->angle);
    cubed->dir_y = sin(cubed->angle);
    cubed->plane_x = -cubed->dir_y * 0.66;
    cubed->plane_y = cubed->dir_x * 0.66;
}

int cubed_render(t_cube *cubed)
{
    double   cos_angle;
    double   sin_angle;

    cubed->new_x = cubed->x;
    cubed->new_y = cubed->y;
    move_cubed(cubed, cubed->dir_x, cubed->dir_y);
    rotate_cubed (cubed);
    cubed->map_x = cubed->x;
    cubed->map_y = cubed->y;
    if (cubed->angle > 2 * PI)
    cubed->angle = 0;
    if (cubed->angle < 0)
    cubed->angle = 2 * PI;
    set_player_dir_and_plane(cubed);
    clear_image(cubed);
    raycasting (cubed, -1);
    draw_map(cubed);
    //put_circle(MINIMAP_X * SIZE, MINIMAP_Y * SIZE, 5, 0x00FF00, cubed);
    put_circle(cubed->x, cubed->y, 5, 0x00FF00, cubed);
    cast_rays_minimap(cubed, -1);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
    return (0);
}

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
    load_texture(cubed, &cubed->tex_west,  "doom4.xpm");*/
    load_texture(cubed, &cubed->tex_north, "eagle.xpm");
    load_texture(cubed, &cubed->tex_south, "greystone.xpm");
    load_texture(cubed, &cubed->tex_east,  "doom.xpm");
    load_texture(cubed, &cubed->tex_west,  "purplestone.xpm");
}

void	cubed_init(t_cube *cubed)
{
	cubed->map = get_map();
	cubed->x = 120;
	cubed->y = 120;
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
    cubed->dir_x = 1;
    cubed->dir_y = 0;
    cubed->plane_x = 0;
    cubed->plane_y = 0.66;
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
