/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:57:06 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/09 13:36:00 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <ft_printf.h>
# include <mlx.h>
# include <math.h>
# include <float.h>
# include <stdio.h>

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

typedef	struct		s_square
{
	int				x;
	int				y;
}					t_square;

typedef	struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef	struct		s_map
{
	struct	s_point	point;
}					t_map;

typedef	struct		s_fdf
{
	void			*mlx;
	void			*win;
	struct	s_map	map;
}					t_fdf;

t_map	my_map(t_map map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_square(t_data *data, t_map map, int color);
void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);
void	draw_square(t_fdf fdf);

//EVENTS FUNCTIONS


#endif
