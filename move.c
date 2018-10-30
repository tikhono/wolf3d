/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:46:50 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/29 14:28:56 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	int i;
	int j;

	i = (int)(a->d.pos_x + a->d.dir_x * a->d.speed);
	i = i < 0 ? 0 : i;
	i = i > a->d.map_h ? a->d.map_h : i;
	j = (int)(a->d.pos_y);
	j = j < 0 ? 0 : j;
	j = j > a->d.map_w ? a->d.map_w : j;
	if ((a->d.map[i][j]) == 0)
		a->d.pos_x += a->d.dir_x * a->d.speed;
	i = (int)(a->d.pos_x);
	i = i < 0 ? 0 : i;
	i = i > a->d.map_h ? a->d.map_h : i;
	j = (int)(a->d.pos_y + a->d.dir_y * a->d.speed);
	j = j < 0 ? 0 : j;
	j = j > a->d.map_w ? a->d.map_w : j;
	if ((a->d.map[i][j]) == 0)
		a->d.pos_y += a->d.dir_y * a->d.speed;
}

void	move_forw(t_all *a)
{
	int i;
	int j;

	i = (int)(a->d.pos_x - a->d.dir_x * a->d.speed);
	i = i < 0 ? 0 : i;
	i = i > a->d.map_h ? a->d.map_h : i;
	j = (int)(a->d.pos_y);
	j = j < 0 ? 0 : j;
	j = j > a->d.map_w ? a->d.map_w : j;
	if ((a->d.map[i][j]) == 0)
		a->d.pos_x -= a->d.dir_x * a->d.speed;
	i = (int)(a->d.pos_x);
	i = i < 0 ? 0 : i;
	i = i > a->d.map_h ? a->d.map_h : i;
	j = (int)(a->d.pos_y - a->d.dir_y * a->d.speed);
	j = j < 0 ? 0 : j;
	j = j > a->d.map_w ? a->d.map_w : j;
	if ((a->d.map[i][j]) == 0)
		a->d.pos_y -= a->d.dir_y * a->d.speed;
}
