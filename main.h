#ifndef MAIN_H
# define MAIN_H
# define HEIGHT 777
# define WIDTH 777
# define BACKGROUND 0xffffff

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include "./libft/libft.h"

struct s_all;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_range
{
	double			min;
	double			max;
}					t_range;

typedef struct		s_data
{
	int				width;
	int				height;
	int				map_w;
	int				map_h;
	int				**map;
	double			cam_x;
	double			cam_y;
	double			dir_x;
	double			dir_y;
	double			new_time;
	double			old_time;
}					t_data;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				x;
	int				y;
	int				z;
}					t_mlx;

typedef struct		s_all
{
	t_mlx			p;
	t_data			d;
	int				*addr;
}					t_all;

int					call_hookers(int key, t_all *a);
int					exit_mouse(void);
int					convert_to_int(t_vec3 color);
void				render(t_all *a);
void				init(t_all *a, char *file);
void				parse(t_all *a);
void				put_pixel(t_all *a, int x, int y, int color);

#endif
