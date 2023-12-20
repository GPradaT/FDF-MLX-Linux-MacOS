/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:57:06 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/20 22:55:22 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft_guillem/libft.h"
# include "../lib/minilibx_macos/mlx.h"
# include <math.h>
# include <float.h>
# include <stdio.h>
# include <fcntl.h>

//WINDOW
# define WIN_WIDTH		(int)1920
# define WIN_HEIGHT		(int)1080
# define OFF_X			0
# define OFF_Y			0
# define ROTATE_D		5
# define MV_PIXELS		5
# define BUFF_SIZE		102400

//COLORS
# define RED		0xFF2222
# define GREEN		0x22FF22
# define BLUE		0x2222FF
# define PURLPLE	0xFF22FF
# define WHITE		0xFFFFFF
# define BLACK		0x000000
# define DARK_GREY	0x444444

//KEY CODES
# define KEY_A				(int)0
# define KEY_S				(int)1
# define KEY_D				(int)2
# define KEY_H				(int)4
# define KEY_G				(int)5
# define KEY_Z				(int)6
# define KEY_X				(int)7
# define KEY_C				(int)8
# define KEY_V				(int)9
# define KEY_B				(int)11
# define KEY_Q				(int)12
# define KEY_W				(int)13
# define KEY_E				(int)14
# define KEY_R				(int)15
# define KEY_Y				(int)16
# define KEY_T				(int)17
# define KEY_1				(int)18
# define KEY_2				(int)19
# define KEY_3				(int)20
# define KEY_4				(int)21
# define KEY_5				(int)23
# define KEY_I				(int)34
# define KEY_P				(int)35
# define KEY_L				(int)37
# define KEY_ESC			(int)53
# define KEY_SUM			(int)69
# define KEY_RES			(int)78
# define KEY_CMD			(int)259
# define KEY_ARROW_LEFT		(int)123
# define KEY_ARROW_RIGHT	(int)124
# define KEY_ARROW_DOWN		(int)125
# define KEY_ARROW_UP		(int)126

//MOUSE CODES
# define LEFT_B		(int)1
# define RIGHT_B	(int)2
# define MIDDLE_B	(int)3
# define SCROLL_UP	(int)4
# define SCROLL_D	(int)5

// REVISAR COMENTARIOS/////

typedef struct	s_vect
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vect;

typedef struct	s_img
{
	int		bpp;
	int		line_len;
	int		endian;
	void	*img;
	char	*data;
	int		width;
	int		height;
}				t_img;

typedef struct	s_iter
{
	int		i;
	int		x;
	int		y;
	int		z;
}				t_iter;

typedef struct	s_line
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		error;
	int		e2;
}				t_line;

typedef struct	s_file
{
	int		fd;
	int		eof;
	char	buffer[BUFF_SIZE + 1];
	char	*contents;
	char	*temp;
	char	**split_y;
	char	**split_x;
}				t_file;

typedef struct	s_map
{
	t_vect	*vect;
	t_vect	prev;
	int		scale;
	int		rows;
	int		columns;
	int		max_z;
	int		z_height;
	int		center_x;
	int		center_y;
	int		rotate_x;
	int		rotate_y;
	int		rotate_z;
	int		move_x;
	int		move_y;
}				t_map;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	char	*file;
	t_img	img;
	t_map	map;
	int		shft;
	int		mode;
	int		color_on;
}				t_fdf;


//-------------		read_map.c		-------------//
void	read_file(t_fdf *fdf, t_file *file);
void	set_vectors(t_fdf *fdf, t_iter *iter, t_file *file);
void	create_map(t_fdf *fdf, t_file *file);
void	set_map(t_fdf *fdf);
void	free_array(void **arr);


//-------------		draw_img.c		-------------//
void	clear_img(t_fdf *fdf);
void	put_img_vector(t_fdf *fdf, t_vect vect);


void	ft_print_line(t_vect a, t_vect b, t_fdf *design);
int	ft_valid_point(t_vect p);

// void draw_lline(t_vect p1, t_vect p2, t_fdf *fdf);
//void	draw_lline(t_point p1, t_point p2, void *mlx_ptr, void *win_ptr);

void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);
//void	draw_line(t_fdf *fdf, t_vect start, t_vect end);
void	put_img_map(t_fdf *fdf);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//void	my_mlx_pixel_put(t_img *img, int x, int y, int color);


//-------------		init.c			-------------//
void	prepare1(t_fdf fdf, t_vect *vect);
void	prepare2(t_fdf fdf, t_vect *vect);
void	set_scale(t_fdf *fdf);
float	set_theta(int degrees);
int	set_color(t_vect *vect, t_map *map);

//-------------		fdf.c			-------------//
void	bad_use(void);
void	check_error(int error, char *msg);
void	init_map(t_fdf *fdf);

void	project_vector(t_fdf *fdf);
void	prepare3(t_fdf c, t_vect *v);
void	prepare4(t_fdf fdf, t_vect *v);
void prepare(t_vect axis, float angle, t_vect *point_to_rotate);
//-------------		moves.c			-------------//
void	rotate_axis(t_fdf *fdf, int *axis, int degrees);
void	adjust_scale(t_fdf *fdf, int direction);
void	move_map(t_fdf *fdf, int *axis, int pixels);
void	adjust_height(t_fdf *fdf, float direction);


int		key_up(int key, t_fdf *c);
int		key_hold(int key, t_fdf *c);
//-------------		draw_img.c		-------------//
/*
t_map	create_map(t_map *map, int **read);


void	create_grid(t_fdf *fdf, int color);




void	my_mlx_square(t_data *data, int color);


void	my_draw_line(t_data *data, int beginX, int beginY, int endX, int endY, int color);


void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);





//EVENTS FUNCTIONS
*/

#endif
