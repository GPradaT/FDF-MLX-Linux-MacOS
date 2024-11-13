/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:57:06 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/13 17:13:11 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft_guillem/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <math.h>
# include <float.h>
# include <stdio.h>
# include <fcntl.h>

//WINDOW
# define WIN_WIDTH		(int)2300
# define WIN_HEIGHT		(int)1200

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
	char	**split_y;
	char	**split_x;
}		t_file;

typedef struct	s_map
{
	t_vect	**vect;
	int	scale;
	int	rows;
	int	columns;
}		t_map;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	char	*file;
	t_img	img;
	t_map	map;
	int	shft;
	int	mode;
	int	color_on;
}		t_fdf;


//-------------		read_map.c		-------------//
void	read_file(t_fdf *fdf, t_file *file);
void	free_array(void **arr);


//-------------		draw_img.c		-------------//
//-------------		init.c			-------------//
//-------------		fdf.c			-------------//
void	bad_use(void);
void	check_error(int error, char *msg);
void	init_map(t_fdf *fdf);
//-------------		moves.c			-------------//
//-------------		draw_img.c		-------------//

#endif
