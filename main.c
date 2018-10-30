/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:56:24 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/30 19:11:21 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_help(t_all *a)
{
	void	*win;

	win = mlx_new_window(a->p.mlx, 200, 150, "HELP");
	mlx_string_put(a->p.mlx, win, 10, 10, 0xFFFFFF, "Q and A - rot x\n");
	mlx_string_put(a->p.mlx, win, 10, 30, 0xFFFFFF, "W and S - rot y\n");
	mlx_string_put(a->p.mlx, win, 10, 50, 0xFFFFFF, "E and D - rot z\n");
	mlx_string_put(a->p.mlx, win, 10, 70, 0xFFFFFF, "R and F - zoom\n");
	mlx_string_put(a->p.mlx, win, 10, 90, 0xFFFFFF, "Arrows  - move\n");
	mlx_hook(a->p.win, 17, 1L << 17, exit_mouse, &a);
}

//	int		temp_time;
//	double	spf;

//	temp_time = clock();
//	spf = (temp_time - a->d.time) / 100000.0;
//	a->d.time = temp_time;
//	a->d.speed = spf * 5.0;
//	a->d.rot = spf * 3.0;


void	init(t_all *a, char *file)
{
	int		x;
	int		y;
	int		z;

	a->d.width = WIDTH;
	a->d.height = HEIGHT;
	a->d.tex_w = 64;
	a->d.tex_h = 64;
	a->d.h = HEIGHT;
	a->d.cam_x = 0;
	a->d.dir_x = -1;
	a->d.dir_y = 0;
	a->d.plane_x = 0;
	a->d.plane_y = 0.66;
	a->d.time = clock();
	a->p.mlx = mlx_init();
	a->p.win = mlx_new_window(a->p.mlx, a->d.width, a->d.height, file);
	a->p.img = mlx_new_image(a->p.mlx, a->d.width, a->d.height);
	a->addr = (int *)mlx_get_data_addr(a->p.img, &x, &y, &z);
}


int		main(int ac, char **av)
{
	t_all	a;

	if (ac < 2)
		return (1);
	while (ac > 2)
		if (fork() != 0)
			--ac;
		else
			break ;
	--ac;
	init(&a, av[ac]);
	parse_map(&a, av[ac]);
//	put_help(&a);
	render(&a);
	mlx_hook(a.p.win, 2, 5, call_hookers, &a);
	mlx_hook(a.p.win, 17, 1L << 17, exit_mouse, &a);
	mlx_loop(a.p.mlx);
	return (0);
}
