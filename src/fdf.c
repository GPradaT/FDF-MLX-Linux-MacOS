/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:06:27 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/19 01:16:13 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


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
	fdf->map.rotate_x = 0;
	fdf->map.rotate_y = 0;
	fdf->map.move_x = 0;
	fdf->map.move_y = 0;
	set_scale(fdf);
	fdf->map.center_x = (WIN_WIDTH - (fdf->map.columns * fdf->map.scale)) / 2;
	fdf->map.center_y = (WIN_HEIGHT - (fdf->map.rows * fdf->map.scale)) / 2;
	fdf->map.z_height = 2;
	put_img_map(fdf);
}

void draw_lline(t_point p1, t_point p2, void *mlx_ptr, void *win_ptr) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float increment_x = (float)dx / (float)steps;
    float increment_y = (float)dy / (float)steps;

    float x = p1.x;
    float y = p1.y;

    int i = 0;
    while (i <= steps) {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFF00F); // Dibuja un píxel en el punto (x, y)
        x += increment_x;
        y += increment_y;
        i++;
    }
}

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
	fdf.img.data = mlx_get_data_addr(fdf.img.img, &fdf.img.bpp,
					&fdf.img.line_len, &fdf.img.endian);
	fdf.shft = 0;
	fdf.mode = 0;
	fdf.color_on = -1;
	set_map(&fdf);
    // draw_isometric(fdf.mlx, fdf.win);
    mlx_hook(fdf.win, 2, 0, key_hold, &fdf);
	mlx_key_hook(fdf.win, key_up, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
