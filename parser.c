/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:57:48 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/31 02:40:28 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	copy_map(t_all *a, char *file, int fd)
{
	int		i;
	int		j;
	int		k;
	char	*line;

	i = 0;
	while (i < a->d.map_h)
	{
		j = 0;
		k = 0;
		if (!get_next_line(fd, &line))
		{
			fprintf(stderr, "Error in %s, incomplete row %d", file, i);
			exit(-1);
		}
		while (j < a->d.map_w)
		{
			a->d.map[i][j] = ft_atoi_i(line, &k);
			++j;
		}
		++i;
	}
	free(line);
}

void	parse_metadata(t_all *a, char *file, int fd, char *line)
{
	get_next_line(fd, &line);
	a->d.map_w = ft_atoi(line);
	get_next_line(fd, &line);
	a->d.map_h = ft_atoi(line);
	get_next_line(fd, &line);
	a->d.pos_x = ft_atoi(line);
	get_next_line(fd, &line);
	a->d.pos_y = ft_atoi(line);
	if (a->d.map_w <= 3 || a->d.map_h <= 3)
	{
		fprintf(stderr, "Failed to open: %s, wrong map size", file);
		exit(-1);
	}
	if (a->d.pos_x < 0 || a->d.pos_y < 0)
	{
		fprintf(stderr, "Position can`t be beyond of map");
		exit(-1);
	}
	if (a->d.pos_x > a->d.map_w || a->d.pos_y > a->d.map_h)
	{
		fprintf(stderr, "Position can`t be beyond of map");
		exit(-1);
	}
	free(line);
}

void	parse_tex(t_all *a)
{
	int		x;
	int		y;
	int		z;
	void	*lol;

	a->d.tex = (int **)malloc(sizeof(int *) * 8);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[0] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[1] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[2] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[3] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[4] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[5] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[6] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./greystone.xpm", &x, &y);
	a->d.tex[7] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
}

void	parse_map(t_all *a, char *file)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open: %s\n", file);
		exit(-1);
	}
	parse_metadata(a, file, fd, line);
	a->d.map = (int **)malloc(sizeof(int *) * a->d.map_h);
	i = 0;
	while (i < a->d.map_w)
		a->d.map[i++] = (int *)malloc(sizeof(int) * a->d.map_w);
	copy_map(a, file, fd);
	if (a->d.map[(int)(a->d.pos_x)][(int)(a->d.pos_y)] != 0)
	{
		fprintf(stderr, "Wrong position: %s\n", file);
		exit(-1);
	}
	parse_tex(a);
}
