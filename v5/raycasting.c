#include "cub3d.h"

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