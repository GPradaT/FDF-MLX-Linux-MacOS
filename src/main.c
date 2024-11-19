/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:20:09 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/19 07:48:39 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

void	draw_mesh(t_img *img)
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
			my_mlx_pixel_put(img, x, y++, 0x00FF0050);
		x += distance_points;
	}

}

void transform_map(t_fdf *fdf)
{
    int x, y;
    t_matrix transform;
    float rotations[3] = {35.264 * M_PI / 180.0, 45.0 * M_PI / 180.0, 0}; // Ángulos X,Y,Z
    float scales[3] = {20.0, 20.0, 20.0};  // Factor de escala
    float translations[3] = {500, 500, 0};  // Centrar en pantalla

    // Inicializar matriz de transformación
    init_transform_matrix(&transform, rotations, scales, translations);

    // Aplicar transformación a cada punto
    y = -1;
    while (++y < fdf->map.rows)
    {
        x = -1;
        while (++x < fdf->map.columns)
        {
            float px = fdf->map.vect[y][x].x;
            float py = fdf->map.vect[y][x].y;
            float pz = fdf->map.vect[y][x].z;

            // Aplicar transformación
            fdf->map.vect[y][x].x = transform.m[0][0] * px + transform.m[0][1] * py
                                   + transform.m[0][2] * pz + transform.m[0][3];
            fdf->map.vect[y][x].y = transform.m[1][0] * px + transform.m[1][1] * py
                                   + transform.m[1][2] * pz + transform.m[1][3];
            fdf->map.vect[y][x].z = transform.m[2][0] * px + transform.m[2][1] * py
                                   + transform.m[2][2] * pz + transform.m[2][3];
			printf("value of fdf->map.vect[y][x].x -> %f\n", fdf->map.vect[y][x].x);
			printf("value of fdf->map.vect[y][x].y -> %f\n", fdf->map.vect[y][x].y);
			printf("value of fdf->map.vect[y][x].z -> %f\n", fdf->map.vect[y][x].z);
        }
    }
}

void	draw_line(t_img *img, int xo, int yo, int xf, int yf, int color)
{
	int dx = abs(xf - xo);
	int dy = abs(yf - yo);
	int sx = xf >= xo ? 1 : -1;
	int sy = yf >= yo ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (xo != xf || yo != yf)
	{
		if (xo >= 0 && xo < 1920 && yo >= 0 && yo < 1080)
			my_mlx_pixel_put(img, xo, yo, color);
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			xo += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			yo += sy;
		}
	}
}

void	draw_map(t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	while (y < fdf->map.rows)
	{
		x = 0;
		while (x < fdf->map.columns)
		{
			if (x < fdf->map.columns - 1)
				draw_line(&fdf->img, fdf->map.vect[y][x].x, fdf->map.vect[y][x].y,
						fdf->map.vect[y][x + 1].x, fdf->map.vect[y][x + 1].y,
						fdf->map.vect[y][x].color);
			if (y < fdf->map.rows - 1)
				draw_line(&fdf->img, fdf->map.vect[y][x].x, fdf->map.vect[y][x].y,
						fdf->map.vect[y + 1][x].x, fdf->map.vect[y + 1][x].y,
						fdf->map.vect[y][x].color);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2 || (ft_strlen(argv[1]) < 4
		|| ft_strncmp(".fdf", &argv[1][ft_strlen(argv[1]) - 4], 4)))
	{
		errno = 2;
		perror("wrong input, what are you trying...?");
		return (errno);
	}

	t_fdf	fdf;
	fdf.file.fd = open(argv[1], O_RDONLY);
	if (fdf.file.fd <= 0)
	{
		errno = EBADF;
		return (errno);
	}
	check_file(&fdf);
	printf("value of fdf->file:\n\n[%s]\n", fdf.file.temp);
	split_map(&fdf);
	set_points(&fdf);
	printf("value of fdf->map.columns -> %d\n", fdf.map.columns);
	printf("VALUE FDF->MAPS->ROWS -> %d\n", fdf.map.rows);
	transform_map(&fdf);

	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "Fil_De_Fer");
	fdf.img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel, &fdf.img.line_length,
								&fdf.img.endian);
	draw_map(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
	mlx_loop(fdf.mlx);
	return (0);
}

