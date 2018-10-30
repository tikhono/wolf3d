#ifndef MAIN_H
# define MAIN_H
# define HEIGHT 512
# define WIDTH 512
# define BACKGROUND 0xffffff

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <sys/time.h>
# include "./libft/libft.h"

typedef struct		s_data
{
	int				width;
	int				height;
	int				map_w;
	int				map_h;
	int				**map;
	int             hit;
	int 			side;
	int 			step_x;
	int 			step_y;
	int				map_x;
	int				map_y;
	int 			line_h;
	int 			h;
	int 			draw_a;
	int 			draw_b;
	clock_t			time;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			cam_x;
	double			cam_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_d_x;
	double			side_d_y;
	double			dx;
	double			dy;
	double			wall_dist;
	double			speed;
	double			rot;
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
void				render(t_all *a);
void				init(t_all *a, char *file);
void				parse(t_all *a);
void				put_pixel(t_all *a, int x, int y, int color);

void				rotate_left(t_all *a);
void				rotate_right(t_all *a);
void				move_forw(t_all *a);
void				move_back(t_all *a);

#endif
