/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:57:06 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/23 22:12:34 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft_guillem/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <errno.h>
# include <float.h>
# include <stdio.h>
# include <fcntl.h>

//KEYS
#  define ESC_KEY 65307
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define W_KEY 119

#  define E_KEY 101
#  define R_KEY 114

#  define V_KEY 118
#  define B_KEY 98

#  define P_KEY 112

#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363


//WINDOW
# define WIN_WIDTH		(int)1920
# define WIN_HEIGHT		(int)1080

typedef struct s_quaternion
{
	float w;
	float x;
	float y;
	float z;
}		t_quaternion;

typedef struct	s_vect
{
	float	x;
	float	y;
	float	z;
	int	color;
}		t_vect;

typedef struct	s_img
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;
	void	*img;
	char	*addr;
}		t_img;

typedef struct	s_file
{
	int	fd;
	int	eof;
	char	*contents;
	char	*temp;
}		t_file;

typedef struct	s_map
{
	t_vect	**vect;
	t_vect	**vect_orig;
	float	scale;
	float	rotation[3];
	float	translation[3];
	int	rows;
	int	columns;
}		t_map;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	t_file	file;
	t_img	img;
	t_map	map;
	int	shft;
	int	mode;
	int	color_on;
	t_quaternion q;
}		t_fdf;

typedef struct	s_matrix
{
	float	m[4][4];
}		t_matrix;



t_quaternion   quaternion_from_axis_angle(float x, float y, float z, float angle);
t_quaternion   quaternion_multiply(t_quaternion q1, t_quaternion q2);
t_vect         rotate_vector(t_vect v, t_quaternion q);
void           normalize_quaternion(t_quaternion *q);
void           update_rotation(t_fdf *fdf, float axis_x, float axis_y, float axis_z, float angle);

//-------------		read_map.c		-------------//
int	check_file(t_fdf *fdf);
int	split_map(t_fdf *fdf);
void	set_points(t_fdf *fdf);

void	read_file(t_fdf *fdf, t_file *file);
void	free_array(void **arr);

void	transform_map(t_fdf *fdf);
void	draw_map(t_fdf *fdf);

int		ft_close(int keycode, t_fdf *fdf);
int		key_hold(int key, t_fdf *fdf);
int		key_up(int key, t_fdf *c);
//-------------		matrix.c		-------------//
void	matrix_identity(t_matrix *matrix);
void	init_transform_matrix(t_matrix *matrix, float rot[3], float scale[3], float trans[3]);
//-------------		draw_img.c		-------------//
//-------------		init.c			-------------//
//-------------		fdf.c			-------------//
void	bad_use(void);
void	check_error(int error, char *msg);
void	init_map(t_fdf *fdf);
//-------------		moves.c			-------------//
//-------------		draw_img.c		-------------//

#endif
