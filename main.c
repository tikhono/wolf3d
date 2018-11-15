/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:56:24 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/31 07:55:07 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_help(t_all *a)
{
	void	*win;

	win = mlx_new_window(a->p.mlx, WIDTH, 150, "HELP");
	mlx_string_put(a->p.mlx, win, 10, 10, 0xFFFFFF, "Arrows and WSDA - move\n");
	mlx_string_put(a->p.mlx, win, 10, 50, 0xFFFFFF, "You are prisoner!\n");
	mlx_string_put(a->p.mlx, win, 10, 90, 0xFFFFFF, "Find sighn and FREEDOM\n");
	mlx_hook(a->p.win, 17, 1L << 17, exit_mouse, &a);
	system("kill all afplay");
	system("afplay start.mp3&");
}

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
	put_help(&a);
	render(&a);
	mlx_hook(a.p.win, 2, 5, call_hookers, &a);
	mlx_hook(a.p.win, 17, 1L << 17, exit_mouse, &a);
	mlx_loop(a.p.mlx);
	return (0);
}
