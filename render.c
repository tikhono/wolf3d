#include "main.h"

void	dda2(t_all *a)
{
	while (a->d.hit == 0)
	{
		if (a->d.side_d_x < a->d.side_d_y)
		{
			a->d.side_d_x += a->d.dx;
			a->d.map_x += a->d.step_x;
			a->d.side = 0;
		}
		else
		{
			a->d.side_d_y += a->d.dy;
			a->d.map_y += a->d.step_y;
			a->d.side = 1;
		}
		if (a->d.map[a->d.map_x][a->d.map_y] > 0)
			a->d.hit = 1;
	}
    if (a->d.side == 0)
        a->d.wall_dist = (a->d.map_x - a->d.pos_x + (1.0 - a->d.step_x) / 2.0) / a->d.ray_dir_x;
    else
        a->d.wall_dist = (a->d.map_y - a->d.pos_y + (1.0 - a->d.step_y) / 2.0) / a->d.ray_dir_y;
}

void	dda1(t_all *a)
{
	if (a->d.ray_dir_x < 0)
	{
		a->d.step_x = -1;
		a->d.side_d_x = (a->d.pos_x - a->d.map_x) * a->d.dx;
	}
	else
	{
		a->d.step_x = 1;
		a->d.side_d_x = (a->d.map_x + 1.0 - a->d.pos_x) * a->d.dx;
	}
	if (a->d.ray_dir_y < 0)
	{
		a->d.step_y = -1;
		a->d.side_d_y = (a->d.pos_y - a->d.map_y) * a->d.dy;
	}
	else
	{
		a->d.step_y = 1;
		a->d.side_d_y = (a->d.map_y + 1.0 - a->d.pos_y) * a->d.dy;
	}
	dda2(a);
}

void	draw(t_all *a, int x)
{
	int 	i;
	int 	color;

	a->d.line_h = (int)((double)(a->d.h) / a->d.wall_dist);
	a->d.draw_a = (int)(-a->d.line_h / 2.0 + (double)(a->d.h) / 2.0);
	a->d.draw_a = a->d.draw_a < 0 ? 0 : a->d.draw_a;
	a->d.draw_b = (int)(a->d.line_h / 2.0 + (double)(a->d.h) / 2.0);
	a->d.draw_b = a->d.draw_b >= (double)(a->d.h) ? a->d.h - 1 : a->d.draw_b;
	switch(a->d.map[a->d.map_x][a->d.map_y])
	{
		case 1:  color = 0x00ff0000;  break; //red
		case 2:  color = 0x0000ff00;  break; //green
		case 3:  color = 0x000000ff;   break; //blue
		case 4:  color = 0x00ffffff;  break; //white
		default: color = 0x0; break; //yellow
	}
	i = a->d.draw_a;
	while (i < a->d.draw_b)
	{
		a->addr[WIDTH * i + x] = color;
		++i;
	}
}

void	render(t_all *a)
{
	int		x;

	a->d.speed = 0.5;
	a->d.rot = 0.1;
	ft_bzero(a->addr, HEIGHT * WIDTH * sizeof(int));
	x = 0;
	while (x < WIDTH)
	{
		a->d.cam_x = 2 * x / (double)(WIDTH) - 1;
		a->d.ray_dir_x = a->d.dir_x + a->d.plane_x * a->d.cam_x;
		a->d.ray_dir_y = a->d.dir_y + a->d.plane_y * a->d.cam_x;
		a->d.map_x = (int)(a->d.pos_x);
		a->d.map_y = (int)(a->d.pos_y);
		a->d.dx = fabs(1 / a->d.ray_dir_x);
		a->d.dy = fabs(1 / a->d.ray_dir_y);
		a->d.hit = 0;
		dda1(a);
		draw(a, x);
		++x;
	}
	mlx_put_image_to_window(a->p.mlx, a->p.win, a->p.img, 0, 0);
}
