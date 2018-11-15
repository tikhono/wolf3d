/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:46:50 by atikhono          #+#    #+#             */
/*   Updated: 2018/11/15 15:07:00 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	win(t_all *a)
{
	void	*win;

	win = mlx_new_window(a->p.mlx, WIDTH, 150, "The end");
	mlx_string_put(a->p.mlx, win, 10, 10, 0xFFFFFF, "You beat this!\n");
	mlx_string_put(a->p.mlx, win, 10, 40, 0xFFFFFF, "Well done!\n");
	mlx_hook(a->p.win, 17, 1L << 17, exit_mouse, &a);
	system("killall afplay");
	system("afplay ./win.mp3&");
}

void	rotate_left(t_all *a)
{
	double	temp;

	temp = a->d.dir_x;
	a->d.dir_x = temp * cos(a->d.rot) - a->d.dir_y * sin(a->d.rot);
	a->d.dir_y = temp * sin(a->d.rot) + a->d.dir_y * cos(a->d.rot);
	temp = a->d.plane_x;
	a->d.plane_x = temp * cos(a->d.rot) - a->d.plane_y * sin(a->d.rot);
	a->d.plane_y = temp * sin(a->d.rot) + a->d.plane_y * cos(a->d.rot);
}

void	rotate_right(t_all *a)
{
	double	temp;

	temp = a->d.dir_x;
	a->d.dir_x = temp * cos(-a->d.rot) - a->d.dir_y * sin(-a->d.rot);
	a->d.dir_y = temp * sin(-a->d.rot) + a->d.dir_y * cos(-a->d.rot);
	temp = a->d.plane_x;
	a->d.plane_x = temp * cos(-a->d.rot) - a->d.plane_y * sin(-a->d.rot);
	a->d.plane_y = temp * sin(-a->d.rot) + a->d.plane_y * cos(-a->d.rot);
}

void	move_back(t_all *a)
{
	double	i;
	double	j;
	double	x;
	double	y;

	x = a->d.pos_x;
	y = a->d.pos_y;
	if (a->d.dir_x >= 0)
		i = x + 2 * a->d.speed;
	else
		i = x - 2 * a->d.speed;
	if (a->d.dir_y >= 0)
		j = y + a->d.speed;
	else
		j = y - a->d.speed;
	if (a->d.map[(int)(i)][(int)(j)] == 0 && a->d.map[(int)(i)][(int)(y)] == 0)
		a->d.pos_x += a->d.dir_x * a->d.speed;
	if (a->d.dir_x >= 0)
		i = x + a->d.speed;
	else
		i = x - a->d.speed;
	if (a->d.dir_y >= 0)
		j = y + 2 * a->d.speed;
	else
		j = y - 2 * a->d.speed;
	if (a->d.map[(int)(i)][(int)(j)] == 0 && a->d.map[(int)(x)][(int)(j)] == 0)
		a->d.pos_y += a->d.dir_y * a->d.speed;
	if (a->d.map[(int)(i)][(int)(j)] == 7)
		win(a);
}

void	move_forw(t_all *a)
{
	double	i;
	double	j;
	double	x;
	double	y;

	x = a->d.pos_x;
	y = a->d.pos_y;
	if (a->d.dir_x < 0)
		i = x + 2 * a->d.speed;
	else
		i = x - 2 * a->d.speed;
	if (a->d.dir_y < 0)
		j = y + a->d.speed;
	else
		j = y - a->d.speed;
	if (a->d.map[(int)(i)][(int)(j)] == 0 && a->d.map[(int)(i)][(int)(y)] == 0)
		a->d.pos_x -= a->d.dir_x * a->d.speed;
	if (a->d.dir_x < 0)
		i = x + a->d.speed;
	else
		i = x - a->d.speed;
	if (a->d.dir_y < 0)
		j = y + 2 * a->d.speed;
	else
		j = y - 2 * a->d.speed;
	if (a->d.map[(int)(i)][(int)(j)] == 0 && a->d.map[(int)(x)][(int)(j)] == 0)
		a->d.pos_y -= a->d.dir_y * a->d.speed;
	if (a->d.map[(int)(i)][(int)(j)] == 7)
		win(a);
}
