/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:20:09 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/13 17:24:47 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

void	draw_mesh(t_data *img)
{
	//X will go --
	//Y will go |
	int x = 0;
	int y = 0;

	int distance_points = 15;

	while (y < MAX_HEIGHT)
	{
		x = 0;
		while (x < MAX_WIDTH)
			my_mlx_pixel_put(img, x++, y, 0x00FF0000);
		y += distance_points;
	}
	x = 0;
	while (x < MAX_WIDTH)
	{
		y = 0;
		while (y < MAX_HEIGHT)
			my_mlx_pixel_put(img, x, y++, 0x00FF0000);
		x += distance_points;
	}

}

#include <errno.h>
int	main(int argc, char **argv)
{
	if (argc != 2 || (ft_strlen(argv[1]) < 4 || ft_strncmp(".fdf", &argv[1][ft_strlen(argv[1]) - 4], 4)))
	{
		errno = 2;
		perror("wrong input, what are you trying...?");
		return (errno);
	}


	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Fil_De_Fer");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	draw_mesh(&img);	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
/*
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
}*/
