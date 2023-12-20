/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:20:09 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/20 11:05:33 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

typedef	struct	s_vec3d {
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef	struct	s_data {
	int		bytespp;
	int		linelen;
	int		endian;
	void	*img;
	char	*data;
	int		width;
	int		height;
	float	centerx;
	float	centery;
}				t_data;

typedef	struct	s_prj2d {
	float	x;
	float	y;
}				t_prj2d;

typedef struct	s_draw {
	void	*mlx;
	void	*win;
	t_vec3d	*vec3d;
	t_vec3d	prev3d;
	t_prj2d	projected;
	t_data	data;
	int axis[3];

}				t_draw;

int		key_up2(int key)
{
	key == 53 ? exit(0) : 0;
	// key == KEY_B ? adjust_scale(c, -1) : 0;
	// key == KEY_V ? adjust_scale(c, 1) : 0;
	return (0);
}

int		main(void)
{
	t_draw	draw;

	draw.mlx = mlx_init();
	draw.win = mlx_new_window(draw.mlx, WIN_WIDTH, WIN_HEIGHT, ">> GPradaT <<");
	draw.data.width = WIN_WIDTH - OFF_X;
	draw.data.height = WIN_HEIGHT - OFF_Y;
	draw.data.img = mlx_new_image(draw.mlx, draw.data.width, draw.data.height);
	draw.data.img = mlx_get_data_addr(draw.data.img, &draw.data.bytespp,
					&draw.data.linelen, &draw.data.endian);
//---	STARTING CODING

	draw.data.center_x =

	t_vec3d	vec1, vec2, vec3;
	vec1.x = 3.0;
	vec1.y = 8.5;
	vec1.z = 1.0;
	vec2.x = 2.0;
	vec2.y = 12.0;
	vec2.z = 0.0;
	vec3.x = -7.0;
	vec3.y = -12.3;
	vec3.z = -7;




//---	ENDING CODING

//	mlx_hook(draw.win, 2, 0, key_hold, &draw);
	mlx_key_hook(draw.win, key_up2, &draw);
	mlx_loop(draw.mlx);
	return (0);
}
