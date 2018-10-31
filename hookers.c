/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:27:07 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/31 07:27:59 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		call_hookers(int key, t_all *a)
{
	if (key == 3)
		a->d.trigger = a->d.trigger == 0 ? 1 : 0;
	if (key == 53)
		exit(0);
	if (key == 123 || key == 0)
		rotate_left(a);
	if (key == 124 || key == 2)
		rotate_right(a);
	if (key == 125 || key == 1)
		move_forw(a);
	if (key == 126 || key == 13)
		move_back(a);
	render(a);
	return (0);
}

int		exit_mouse(void)
{
	exit(0);
}
