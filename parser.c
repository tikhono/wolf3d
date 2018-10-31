/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:57:48 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/31 03:25:44 by atikhono         ###   ########.fr       */
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
			if (i == 0 || j == 0 || i == a->d.map_h - 1 || j == a->d.map_w - 1)
				a->d.map[i][j] = 1;
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

void	get_addr(t_all *a, int num, void *lol)
{
	int		x;
	int		y;
	int		z;

	if (lol == NULL)
	{
		fprintf(stderr, "Texture number %d missing", num);
		exit(-1);
	}
	a->d.tex[num] = (int *)mlx_get_data_addr(lol, &x, &y, &z);
}

void	parse_tex(t_all *a)
{
	int		x;
	int		y;
	int		num;
	void	*lol;

	num = 0;
	a->d.tex = (int **)malloc(sizeof(int *) * 8);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/barrel.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/greystone.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/bluestone.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/colorstone.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/purpulstone.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/redbrick.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/wood.xpm", &x, &y);
	get_addr(a, num++, lol);
	lol = mlx_xpm_file_to_image(a->p.mlx, "./textures/eagle.xpm", &x, &y);
	get_addr(a, num, lol);
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
