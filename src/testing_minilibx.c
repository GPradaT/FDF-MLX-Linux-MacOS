/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_minilibx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:59:41 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/07 16:03:16 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fdf.h>

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int	y, x;
	int z, height;

	z = 0;
	x = 0;
	y = 0;
	height = 5;
	img.line_len = 100;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len,
								&img.endian);
	while (x < WIN_HEIGHT && y < WIN_WIDTH)
	{
		my_mlx_pixel_put(&img, x++, y++, 0x00FF0000);
		y = 20;
		while (z < height && y < WIN_WIDTH)
			my_mlx_pixel_put(&img, z++, y++, 0xFFFF0000);
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	return (0);
}
