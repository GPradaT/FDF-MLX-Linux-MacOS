/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:06:27 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/13 12:26:58 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		bad_use();
	fdf.file = argv[1];
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIN_WIDTH, WIN_HEIGHT, ">> GPradaT <<");
	fdf.img.width = WIN_WIDTH - OFF_X;
	fdf.img.height = WIN_HEIGHT - OFF_Y;
	fdf.img.img = mlx_new_image(fdf.mlx, fdf.img.width, fdf.img.height);
	fdf.img.data = (int *)mlx_get_data_addr(fdf.img.img, &fdf.img.bpp,
					&fdf.img.line_len, &fdf.img.endian);
	fdf.shft = 0;
	fdf.mode = 0;
	fdf.color_on = -1;
	set_map(&fdf);
	mlx_hook(fdf.win, 2, 0, key_hold, &fdf);
	mlx_key_hook(fdf.win, key_up, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}

void	bad_use(void)
{
	ft_putstr("\nUse => ./FdF <url/file/directory.fdf>\n");
	exit (0);
}

void	check_error(int error, char *message)
{
	if (error < 1)
	{
		ft_printf("- Error: %s\n", message);
		exit(1);
	}
}


void	init_map(t_fdf *fdf)
{
	fdf->map.rotate_x = 5;
	fdf->map.rotate_y = 0;
	fdf->map.move_x = 0;
	fdf->map.move_y = 0;
	set_scale(fdf);

	fdf->map.center_x = (WIN_WIDTH - (fdf->map.columns * fdf->map.scale)) / 2;
	fdf->map.center_y = (WIN_HEIGHT - (fdf->map.rows * fdf->map.scale)) / 2;
	fdf->map.z_height = 1;
	put_img_map(fdf);
}
