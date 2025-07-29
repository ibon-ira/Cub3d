#include "cub3d.h"

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
    //draw_map(cubed);
    //put_circle(MINIMAP_X * SIZE, MINIMAP_Y * SIZE, 5, 0x00FF00, cubed);
    //put_circle(cubed->x, cubed->y, 5, 0x00FF00, cubed);
    //cast_rays_minimap(cubed, -1);
    mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img_ptr, 0, 0);
    return (0);
}
