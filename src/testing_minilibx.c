/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_minilibx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:59:41 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/09 13:38:13 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	main(void)
{
	t_fdf	fdf;
	t_data	img;
	int x, y;

	x = 1000;
	y = 1000;
	
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "Hello world!");
	
	img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	fdf.map = my_map(fdf.map);
	my_mlx_square(&img, fdf.map, 0x00FF00);
	draw_square(fdf);
	mlx_hook(fdf.win, 2, 53, close, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
