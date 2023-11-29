/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:57:06 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/29 14:02:20 by gprada-t         ###   ########.fr       */
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
# define WIN_WIDTH	(int)900
# define WIN_HEIGHT	(int)1080

//KEY CODES
# define KEY_ESC	(int) 53

//MOUSE CODES
# define LEFT_B		(int)1
# define RIGHT_B	(int)2
# define MIDDLE_B	(int)3
# define SCROLL_UP	(int)4
# define SCROLL_D	(int)5

// REVISAR COMENTARIOS/////

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


//-------------		read_map.c		-------------//
void	init_map(t_fdf *fdf);
void	read_file(t_fdf *fdf, t_file *file);
void	set_vectors(t_fdf *fdf, t_iterators *iter, t_file *file);
void	create_map(t_fdf *fdf, t_file *file);
void	set_map(t_fdf *fdf);


//-------------		draw_img.c		-------------//
void	clear_img(t_fdf *fdf);
void	put_img_vector(t_fdf *fdf, t_vect vect);
void	draw_line(t_fdf *fdf, t_vect start, t_vect end);
void	put_img_map(t_fdf *fdf);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);


//-------------		draw_img.c		-------------//
//-------------		draw_img.c		-------------//
//-------------		draw_img.c		-------------//

t_map	create_map(t_map *map, int **read);


void	create_grid(t_fdf *fdf, int color);




void	my_mlx_square(t_data *data, int color);


void	my_draw_line(t_data *data, int beginX, int beginY, int endX, int endY, int color);


void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);





//EVENTS FUNCTIONS


#endif
