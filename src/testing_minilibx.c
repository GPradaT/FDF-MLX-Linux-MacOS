/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_minilibx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:59:41 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/11 18:58:11 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	main(void)
{
	t_fdf	fdf;
	t_data	img;
	int x, y;

	x = 100;
	y = 100;
	
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "Hello world!");
	
	img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
/*	while (x++ < 500)
		my_mlx_pixel_put(&img, x, y, 0x00FFF0);*/
//	my_draw_line(fdf.data, 100, 100, 100, 500, 0x00FF00);
//	draw_line(fdf.mlx, fdf.win, 100, 100, 300, 100, 0x00FF00);
	fdf.map = my_map(fdf.map);

//	my_mlx_square(&img, 0x00FF00);
	create_grid(&img, 0, 0, 0x00FF00);

	mlx_put_image_to_window(fdf.mlx, fdf.win, img.img, 0, 0);
	create_grid(&img, , 3, 0xFF0000);
//	draw_square(fdf);
//	mlx_hook(fdf.win, 2, 53, close, &fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, img.img, 0, 0);
	mlx_loop(fdf.mlx);
	return (0);
}
