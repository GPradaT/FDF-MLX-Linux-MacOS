/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:57:06 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/29 15:38:38 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <float.h>
# include <stdio.h>
# include <fcntl.h>

//WINDOW
# define WIN_WIDTH		(int)900
# define WIN_HEIGHT		(int)1080
# define OFF_X			0
# define OFF_Y			0
# define ROTATE_D		5
# define MV_PIXELS		5

//COLORS
# define RED		0xFF2222
# define GREEN		0x22FF22
# define BLUE		0x2222FF
# define PURLPLE	0xFF22FF
# define WHITE		0xFFFFFF
# define BLACK		0x000000
# define DARK_GREY	0x444444

//KEY CODES
# define KEY_ESC	(int) 53

//MOUSE CODES
# define LEFT_B		(int)1
# define RIGHT_B	(int)2
# define MIDDLE_B	(int)3
# define SCROLL_UP	(int)4
# define SCROLL_D	(int)5

// REVISAR COMENTARIOS/////

typedef struct	s_vect
{
	int		x;
	int		y;
	int		z;
	int		color;
}				t_vect;

typedef struct	s_img
{
	int		bpp;
	int		line_len;
	int		endian;
	void	*img;
	int		*data;
	int		width;
	int		height;
}				t_img;

typedef struct	s_iterator
{
	int		i;
	int		x;
	int		y;
	int		z;
}				t_iterator;

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
	char	*buffer[BUFFER_SIZE + 1];
	char	*contents;
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
/*

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};



typedef	struct		s_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_data;

typedef	struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef	struct		s_map
{
	struct s_point	*vectors;
	int				max_z;
	float			z_height;
	struct	s_point	end_p;
	struct	s_point	vector;
}					t_map;

typedef	struct		s_fdf
{
	void			*mlx;
	void			*win;
	struct	s_map	*map;
	struct	s_data	*data;
}					t_fdf;
*/

//-------------		read_map.c		-------------//
void	init_map(t_fdf *fdf);
void	read_file(t_fdf *fdf, t_file *file);
void	set_vectors(t_fdf *fdf, t_iterator *iter, t_file *file);
void	create_map(t_fdf *fdf, t_file *file);
void	set_map(t_fdf *fdf);


//-------------		draw_img.c		-------------//
void	clear_img(t_fdf *fdf);
void	put_img_vector(t_fdf *fdf, t_vect vect);
void	draw_line(t_fdf *fdf, t_vect start, t_vect end);
void	put_img_map(t_fdf *fdf);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);


//-------------		init.c			-------------//
void	init(t_fdf fdf, t_vect *vect);
void	set_scale(t_fdf *fdf);
float	set_theta(int degrees);
void	set_color(t_vect *vect, t_map *map);

//-------------		fdf.c			-------------//
void	if_error(int error, char *msg);
void	free_array(void **array);

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
