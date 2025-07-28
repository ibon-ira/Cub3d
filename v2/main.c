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

double fixed_dist(double x1, double y1, double x2, double y2, t_cube *cubed)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    double angle = atan2(delta_y, delta_x) - cubed->angle;
    double fix_dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(angle);
    return fix_dist;
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

/*void    draw_colum(t_cube *cubed, int i)
{
        double dist;
        double height;
        int start_y;
        int end;
        
        dist = fixed_dist(cubed->x, cubed->y, cubed->ray_x, cubed->ray_y, cubed);
        height = (SIZE / dist) * ((WIDTH / 2) / tan(POV / 2));
        start_y = (HEIGHT - height) / 2;
        end = start_y + height;
     
        draw_3d (i, start_y, end, cubed);
}*/


/*void draw_colum(t_cube *cubed, int i)
{
    double dist = fixed_dist(cubed->x, cubed->y, cubed->ray_x, cubed->ray_y, cubed);

    double height = (SIZE / dist) * ((WIDTH / 2) / tan(POV / 2));
    int line_height = (int)height;
    int start_y = (HEIGHT - line_height) / 2;
    int end_y = start_y + line_height;

    if (start_y < 0)
        start_y = 0;
    if (end_y > HEIGHT)
        end_y = HEIGHT;

    // === TEX_X: calcular coordenada horizontal del impacto
    double wall_hit_x;
    if (ray_angle > 0 && ray_angle < PI)
        if (cubed->map[(int)((cubed->ray_y + 1) / SIZE)][(int)(cubed->ray_x / SIZE)] == '0')
            wall_hit_x = fmod(cubed->ray_y, SIZE);
    else
        wall_hit_x = fmod(cubed->ray_x, SIZE);
    if (ray_angle < 2*PI && ray_angle > PI)
        if (cubed->map[(int)((cubed->ray_y - 1) / SIZE)][(int)(cubed->ray_x / SIZE)] == '0')
            wall_hit_x = fmod(cubed->ray_y, SIZE);
    else
        wall_hit_x = fmod(cubed->ray_x, SIZE);
    if (cubed->map[(int)(cubed->ray_y / SIZE)][(int)(cubed->ray_x / SIZE)] == '1')
        wall_hit_x = fmod(cubed->ray_y, SIZE);
    else
        wall_hit_x = fmod(cubed->ray_x, SIZE);
    double dx = fabs(cubed->ray_x - cubed->x);
    double dy = fabs(cubed->ray_y - cubed->y);

    if (dx > dy)
        wall_hit_x = fmod(cubed->ray_y, SIZE);
    else
        wall_hit_x = fmod(cubed->ray_x, SIZE);
    if (wall_hit_x < 0)
        wall_hit_x += SIZE;

    int tex_x = (int)((wall_hit_x / SIZE) * cubed->tex_width);

    // === PINTAR LA COLUMNA DE PIXELES CON TEXTURA ===
    for (int y = start_y; y < end_y; y++)
    {
        // Calcular coordenada Y en la textura
        int d = y * 256 - HEIGHT * 128 + line_height * 128;
        int tex_y = ((d * cubed->tex_height) / line_height) / 256;

        // Obtener color de la textura
        int color_offset = (tex_y * cubed->tex_width + tex_x) * 4;
        int color = *(int *)(cubed->tex_data + color_offset);

        put_pixel(i, y, color, cubed);
    }

    // Opcional: cielo
    for (int y = 0; y < start_y; y++)
        put_pixel(i, y, 0x87CEEB, cubed); // color cielo

    // Opcional: suelo
    for (int y = end_y; y < HEIGHT; y++)
        put_pixel(i, y, 0x444444, cubed); // color suelo
}*/

/*void raycasting(t_cube *cubed, int i)
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
        draw_colum(cubed, i);
        ray_angle += delta_angle;
    }
}*/

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

/*void draw_3d_dda(int i, int start_y, int end_y, t_cube *cubed)
{
    int tex_x;
    
    tex_x = (int)(cubed->wall_x * cubed->tex_width);
    if (cubed->side == 0 && cubed->ray_dir_x > 0)
        tex_x = cubed->tex_width - tex_x - 1;
    if (cubed->side == 1 && cubed->ray_dir_y < 0)
        tex_x = cubed->tex_width - tex_x - 1;

    for (int y = start_y; y < end_y; y++)
    {
        int d = y * 256 - HEIGHT * 128 + cubed->line_height * 128;
        int tex_y = (d * cubed->tex_height) / cubed->line_height / 256;

        int offset = tex_y * cubed->tex_line_len + tex_x * (cubed->tex_bpp / 8);
        int color = *(int *)(cubed->tex_data + offset);

        put_pixel(i, y, color, cubed);
    }

    // Sky
    for (int y = 0; y < start_y; y++)
        put_pixel(i, y, 0x87CEEB, cubed);  // Azul cielo

    // Floor
    for (int y = end_y; y < HEIGHT; y++)
        put_pixel(i, y, 0x444444, cubed);  // Gris piso
}*/
void draw_3d_dda(int x, int start_y, int end_y, t_cube *cubed)
{
    t_texture *tex = cubed->current_tex;

    double wall_x = cubed->wall_x - floor(cubed->wall_x);
    int tex_x = (int)(wall_x * tex->width);

    if ((cubed->side == 0 && cubed->ray_dir_x > 0) || 
        (cubed->side == 1 && cubed->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    for (int y = start_y; y < end_y; y++)
    {
        int d = y * 256 - HEIGHT * 128 + cubed->line_height * 128;
        int tex_y = (d * tex->height) / cubed->line_height / 256;

        int offset = tex_y * tex->line_len + tex_x * (tex->bpp / 8);
        int color = *(int *)(tex->data + offset);

        put_pixel(x, y, color, cubed);
    }

    for (int y = 0; y < start_y; y++)
        put_pixel(x, y, 0x87CEEB, cubed);
    for (int y = end_y; y < HEIGHT; y++)
        put_pixel(x, y, 0x444444, cubed);
}

void select_texture(t_cube *cubed)
{
    if (cubed->side == 0)
        cubed->current_tex = (cubed->ray_dir_x > 0) ? &cubed->tex_west : &cubed->tex_east;
    else
        cubed->current_tex = (cubed->ray_dir_y > 0) ? &cubed->tex_north : &cubed->tex_south;
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
        //draw_colums_dda(cubed, i);
	    select_texture(cubed);
	    //draw_textured_line(cubed, x, cubed->texture, wall_x);
        start_y = (HEIGHT - cubed->line_height) / 2;
        end = start_y + cubed->line_height;
        if (start_y < 0)
	        start_y = 0;
        if (end > HEIGHT)
	        end = HEIGHT;
        draw_3d_dda(i, start_y, end, cubed);
	}
}

int is_wall(t_cube *cubed, int pos_x, int pos_y)
{
    if (cubed->map[pos_y / SIZE][pos_x / SIZE] == '1')
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
   // double plane_length;

    cubed->dir_x = cos(cubed->angle);
    cubed->dir_y = sin(cubed->angle);
    //plane_length = tan(POV / 2); // POV en radianes
    cubed->plane_x = -cubed->dir_y * 0.66;//plane_length;
    cubed->plane_y = cubed->dir_x * 0.66;//plane_length;
}

int cubed_render(t_cube *cubed)
{
    double   cos_angle;
    double   sin_angle;


    cubed->new_x = cubed->x;
    cubed->new_y = cubed->y;
    rotate_cubed (cubed);
    if (cubed->angle > 2 * PI)
    cubed->angle = 0;
    if (cubed->angle < 0)
    cubed->angle = 2 * PI;
    set_player_dir_and_plane(cubed);
    move_cubed(cubed, cubed->dir_x, cubed->dir_y);
    clear_image(cubed);
    raycasting (cubed, -1);
    //draw_map(cubed);
    //put_circle(MINIMAP_X * SIZE, MINIMAP_Y * SIZE, 5, 0x00FF00, cubed);
    //put_circle(cubed->x, cubed->y, 5, 0x00FF00, cubed);
    //cast_rays_minimap(cubed, -1);
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
    load_texture(cubed, &cubed->tex_north, "doom.xpm");
    load_texture(cubed, &cubed->tex_south, "doom2.xpm");
    load_texture(cubed, &cubed->tex_east,  "doom3.xpm");
    load_texture(cubed, &cubed->tex_west,  "doom4.xpm");
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
    /*cubed->tex_ptr = mlx_xpm_file_to_image(cubed->mlx, "doom.xpm", &cubed->tex_width, &cubed->tex_height);
    if (!cubed->tex_ptr)
    {
        printf("Error loading texture\n");
        exit(1);
    }*/
    load_all_textures(cubed);
    //cubed->tex_data = mlx_get_data_addr(cubed->tex_ptr, &cubed->tex_bpp, &cubed->tex_line_len, &cubed->tex_endian);
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
	mlx_loop_hook(cubed.mlx, cubed_render, &cubed);
	mlx_loop(cubed.mlx);
	return (0);
}
