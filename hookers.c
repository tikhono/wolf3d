/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:27:07 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/29 12:59:30 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		call_hookers(int key, t_all *a)
{

	if (key == 53)
	{
		exit(0);
		return (0);
	}
	if (key == 123)
		rotate_left(a);
	if (key == 124)
		rotate_right(a);
	if (key == 125)
		move_forw(a);
	if (key == 126)
		move_back(a);
//	printf("%f %f\t%f\n", a->d.pos_x, a->d.pos_y, a->d.speed);
	render(a);
	return (0);
}

int		exit_mouse(void)
{
	exit(0);
	return (0);
}
