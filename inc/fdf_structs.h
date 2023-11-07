/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:00:19 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/02 18:05:33 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_STRUCTS_H
# define FDF_STRUCTS_H
# include "fdf.h"

//COLORS DEFINITION

# define WHITE		(int)0x00FFFFFF
# define BLACK		(int)0x00000000
# define RED		(int)0x00FF0000
# define GREEN		(int)0x0000FF00
# define BLUE		(int)0x000000FF
# define LIGHT_BLUE	(int)0x0051D1F6
# define YELLOW		(int)0x00FFFF99
# define ORANGE		(int)0x00FFA500
# define LIGHT_GRAY	(int)0x00888888
# define GRAY		(int)0x00555555
# define CYAN		(int)0x0017E0E3
# define D_GRAY		(int)0x00222222
# define PINK		(int)0x00FF66FF
# define N_GRAY		(int)0x00F1F0E6
# define BROWN		(int)0x00562B05

///Palette -> Neon
# define FUSCHIA		(int)0x00A239CA
# define VOID			(int)0x000E0B16
# define JEWEL			(int)0x004717F6

///Palettes id
# define P_DEF			(int)0
# define P_REAL			(int)1
# define P_NEON			(int)2
# define P_BW			(int)3
# define P_WB			(int)4

//EVENT CODES
# define E_KEY_P 		(int)2
# define E_KEY_R 		(int)3
# define E_BTN_P 		(int)4
# define E_BTN_R 		(int)5
# define E_PTR_M 		(int)6
# define E_DESTROY_N	(int)17

//EVENTS MASKS
# define KEY_P_MASK 	(long)1
# define KEY_R_MASK 	(long)2
# define BTN_P_MASK 	(long)4
# define BTN_R_MASK 	(long)8
# define PTR_M_MASK 	(long)64
# define DESTROY_N_MASK	(long)131072

//STRUCTURES DEFINITIONS

typedef struct s_design		t_design;
typedef struct s_point		t_point;
typedef struct s_pixmap		t_pixmap;
typedef struct s_color		t_color;
typedef struct s_events		t_events;
typedef struct s_palette	t_palette;
typedef struct s_stat		t_stat;
typedef struct s_property	t_property;

struct s_point {
	float	x;
	float	y;
	float	z;
	float	r;
	float	fi;
	float	fita;
	int		color;
	float	select;
	char	hexa;
};

struct s_pixmap {
	void	*img;
	char	*addr;
	int		bpp;
	int		bytes_pp;
	int		line_len;
	int		endian;
};

struct	s_color {
	int		top;
	int		std;
	int		btm;
	int		bckg;
	int		menu;
	int		id;
};

struct	s_events {
	float		scale;
	int			show_menu;
	int			sphere;
	int			shadow;
	int			k_cmd;
	int			put_pt;
	t_point		btn_l;
	t_point		btn_r;
	t_point		sel_line;
	t_point		zoom;
	t_point		shift;
	t_point		sel_point;
};

struct	s_palette {
	t_color		def;
	t_color		wb;
	t_color		bw;
	t_color		real;
	t_color		neon;
};

struct	s_stat {
	int			width;
	int			height;
	int			max_z;
	int			min_z;
	int			size;
	int			inc_x;
	int			inc_y;
};

struct	s_property {
	float		z_div;
	int			density;
	float		angle[3];
	float		new_center[2];
	int			lines;
	int			dots;
	int			lim_z;
};

struct s_design {
	t_stat		info;
	t_property	prop;
	t_events	event;
	t_color		color;
	t_palette	palette;
	t_point		*points;
	t_point		*copy;
	t_pixmap	pixmap;
	char		*map_name;
	char		*map;
	void		*mlx;
	void		*mlx_win;
};

#endif
