/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atikhono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:57:48 by atikhono          #+#    #+#             */
/*   Updated: 2018/10/28 17:39:35 by atikhono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_exit(char *file, int i, int j)
{
	++i;
	++j;
	fprintf(stderr, "Error in %s, value at row: %i, col: %i\n", file, i, j);
	exit(-1);
}

void	put(t_pix ***arr, char **buf, t_buff_i *b, char *file)
{
	char	**temp;

	while (buf[b->j] != NULL)
	{
		temp = ft_strsplit(buf[b->j], ',');
		if (ft_num_of_rows(temp) > 2 || !ft_isnum(temp[0], 10))
			ft_exit(file, b->i, b->j);
		if (ft_strchr(buf[b->j], ',') != NULL)
			if (*(ft_strchr(buf[b->j], ',') + 1) != '0')
				ft_exit(file, b->i, b->j);
		if (temp[1] != NULL)
			if ((!ft_isnum(temp[1], 16)) || (ft_strlen(temp[1]) >= 10))
				ft_exit(file, b->i, b->j);
		arr[b->i][b->j] = (t_pix *)malloc(sizeof(t_pix));
		arr[b->i][b->j]->oz = ft_atoi(temp[0]);
		arr[b->i][b->j]->x = b->j;
		arr[b->i][b->j]->y = b->i;
		arr[b->i][b->j]->z = arr[b->i][b->j]->oz;
		free(buf[b->j++]);
	}
}

t_pix	***fill(t_pix ***arr, int fd, t_buff_i *b, char *file)
{
	char	*line;
	char	**buf;
	int		rows;

	while (get_next_line(fd, &line))
	{
		buf = ft_strsplit(line, ' ');
		free(line);
		b->j = 0;
		rows = ft_num_of_rows(buf);
		if (b->i == 0)
			b->c = rows;
		else if (b->c != rows)
			ft_exit(file, b->i, b->j);
		arr[b->i] = (t_pix **)malloc(sizeof(t_pix *) * (rows + 1));
		arr[b->i][rows] = NULL;
		put(arr, buf, b, file);
		free(buf);
		++b->i;
	}
	close(fd);
	free(line);
	if ((arr[0][1] == NULL && arr[1] == NULL))
		ft_exit(file, 0, 0);
	return (arr);
}

t_pix	***parse(char *file)
{
	int			fd;
	int			rows;
	t_buff_i	b;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open: %s\n", file);
		exit(-1);
	}

	return (fill(arr, fd, &b, file));
}
