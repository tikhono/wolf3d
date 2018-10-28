/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hookers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 11:27:07 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/28 20:04:18 by atikhono         ###   ########.fr       */
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
		a->d
	if (key == 124)
		a->d.off_x += 0.1 * a->d.scale;
	if (key == 125)
		a->d.off_y += 0.1 * a->d.scale;
	if (key == 126)
		a->d.off_y -= 0.1 * a->d.scale;
	return (0);
}

int		exit_mouse(void)
{
	exit(0);
	return (0);
}
