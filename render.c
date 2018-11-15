/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 02:45:21 by atikhono          #+#    #+#             */
/*   Updated: 2018/11/08 16:54:11 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		a->d.wall_dist = (a->d.map_x - a->d.pos_x +
				(1.0 - a->d.step_x) / 2.0) / a->d.ray_dir_x;
	else
		a->d.wall_dist = (a->d.map_y - a->d.pos_y +
				(1.0 - a->d.step_y) / 2.0) / a->d.ray_dir_y;
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

void	vert_line(t_all *a, int x, int color)
{
	int		y;
	int		d;

	y = a->d.draw_a;
	while (y < a->d.draw_b)
	{
		d = y * 256 - a->d.h * 128 + a->d.line_h * 128;
		a->d.tex_y = ((d * a->d.tex_h) / a->d.line_h) / 256;
		a->d.tex_id = a->d.tex_id > 7 ? 7 : a->d.tex_id;
		a->d.tex_id = a->d.tex_id < 0 ? 0 : a->d.tex_id;
		color = a->d.tex[a->d.tex_id][a->d.tex_h * a->d.tex_y + a->d.tex_x];
		if (a->d.trigger == 0)
		{
			if (a->d.side == 0 && a->d.ray_dir_x > 0)
				color = 0xff0000;
			else if (a->d.side == 0 && a->d.ray_dir_x < 0)
				color = 0x00ff00;
			else if (a->d.side == 1 && a->d.ray_dir_y > 0)
				color = 0x0000ff;
			else if (a->d.side == 1 && a->d.ray_dir_y < 0)
				color = 0xffff00;
		}
		a->addr[WIDTH * y + x] = color;
		++y;
	}
}

void	draw(t_all *a, int x)
{
	int		color;

	color = 0;
	a->d.line_h = (int)((double)(a->d.h) / a->d.wall_dist);
	a->d.draw_a = (int)(-a->d.line_h / 2.0 + (double)(a->d.h) / 2.0);
	a->d.draw_a = a->d.draw_a < 0 ? 0 : a->d.draw_a;
	a->d.draw_b = (int)(a->d.line_h / 2.0 + (double)(a->d.h) / 2.0);
	a->d.draw_b = a->d.draw_b >= (double)(a->d.h) ? a->d.h - 1 : a->d.draw_b;
	a->d.tex_id = a->d.map[a->d.map_x][a->d.map_y];
	if (a->d.side == 0)
		a->d.wall_x = a->d.pos_y + a->d.wall_dist * a->d.ray_dir_y;
	else
		a->d.wall_x = a->d.pos_x + a->d.wall_dist * a->d.ray_dir_x;
	a->d.wall_x -= floor(a->d.wall_x);
	a->d.tex_x = (int)(a->d.wall_x * (double)(a->d.tex_w));
	if (a->d.side == 0 && a->d.ray_dir_x > 0)
		a->d.tex_x = a->d.tex_w - a->d.tex_x - 1;
	if (a->d.side == 1 && a->d.ray_dir_y < 0)
		a->d.tex_x = a->d.tex_w - a->d.tex_x - 1;
	vert_line(a, x, color);
}

void	render(t_all *a)
{
	int		x;

	a->d.speed = 0.2;
	a->d.rot = 0.09;
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
