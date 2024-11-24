/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:20:09 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/24 10:43:50 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	char	*d;

	d = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)d = color;
}

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

void	draw_mesh(t_img *img)
{
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
			printf("Drawing line from (%f,%f) to (%f,%f)\n",
			fdf->map.vect[y][x].x, fdf->map.vect[y][x].y,
			fdf->map.vect[y][x + 1].x, fdf->map.vect[y][x + 1].y);
			printf("ROTATION X -> %f\n", fdf->map.rotation[0]);
			printf("ROTATION Y -> %f\n", fdf->map.rotation[1]);
			if (x < fdf->map.columns - 1)
				draw_line(&fdf->img, fdf->map.vect[y][x].x, fdf->map.vect[y][x].y,
						fdf->map.vect[y][x + 1].x, fdf->map.vect[y][x + 1].y,
						fdf->map.vect[y][x].color != 0 ? fdf->map.vect[y][x].color : 0x00FFFF);
			if (y < fdf->map.rows - 1)
				draw_line(&fdf->img, fdf->map.vect[y][x].x, fdf->map.vect[y][x].y,
						fdf->map.vect[y + 1][x].x, fdf->map.vect[y + 1][x].y,
						0x00FF0000);
			x++;
		}
		y++;
	}

}

int ft_close(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(0);
	return (0);
}

void init_map(t_fdf *fdf)
{
    printf("Iniciando mapa en: %p\n", (void*)fdf);
    ft_memset(&fdf->map, 0, sizeof(t_map));
    fdf->map.scale = 20.0f;
    fdf->map.rotation[0] = 35.0f;
    fdf->map.rotation[1] = 45.0f;
    fdf->map.rotation[2] = 0.0f;
    fdf->map.translation[0] = 0;
    fdf->map.translation[1] = 0;
    fdf->q.w = 1.0f;
    fdf->q.x = 0.0f;
    fdf->q.y = 0.0f;
    fdf->q.z = 0.0f;
}

t_quaternion	q_from_axis_angle(float x, float y, float z, float angle)
{
	t_quaternion	q;

	q.w = cos(angle / 2.0f);
	q.x = x * sin(angle / 2.0f);
	q.y = y * sin(angle / 2.0f);
	q.z = z * sin(angle / 2.0f);
	return (q);
}

t_quaternion	q_multiply(t_quaternion qa, t_quaternion qb)
{
	t_quaternion	result;

	result.w = qa.w * qb.w - qa.x * qb.x - qa.y * qb.y - qa.z * qb.z;
	result.x = qa.w * qb.x + qa.x * qb.w + qa.y * qb.z - qa.z * qb.y;
	result.y = qa.w * qb.y - qa.x * qb.z + qa.y * qb.w + qa.z * qb.x;
	result.z = qa.w * qb.z + qa.x * qb.y - qa.y * qb.x + qa.z * qb.w;
	return (result);
}

t_vect		rotate_vector(t_vect v, t_quaternion q)
{
	t_quaternion	p = {0, v.x, v.y, v.z};
	t_quaternion	q_conj = {q.w, -q.x, -q.y, -q.z};
	t_quaternion	result;
	t_vect		rotated;

	result = q_multiply(q_multiply(q, p), q_conj);
	rotated.x = result.x;
	rotated.y = result.y;
	rotated.z = result.z;
	rotated.color = v.color;
	return (rotated);
}

void	transform_map(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fdf->map.rows)
	{
		x = -1;
		while (++x < fdf->map.columns)
		{
			fdf->map.v_tmp = rotate_vector(fdf->map.vect_orig[y][x], fdf->q);
			fdf->map.v_tmp.x *= fdf->map.scale;
			fdf->map.v_tmp.y *= fdf->map.scale;
			fdf->map.v_tmp.z *= fdf->map.scale;
			fdf->map.v_tmp.x += (WIN_WIDTH) + fdf->map.translation[0];
			fdf->map.v_tmp.y += (WIN_HEIGHT / 2) + fdf->map.translation[1];
			fdf->map.vect[y][x] = fdf->map.v_tmp;
		}
	}
}

void	normalize_quaternion(t_quaternion *q)
{
	float	norm;

	norm = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
	q->w /= norm;
	q->x /= norm;
	q->y /= norm;
	q->z /= norm;
}

void	update_rotation(t_fdf *f, float a_x, float a_y, float a_z, float angle)
{
	t_quaternion	delta;

	delta = q_from_axis_angle(a_x, a_y, a_z, angle);
	f->q = q_multiply(delta, f->q);
	normalize_quaternion(&f->q);
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
	printf("ROTATION X -> %f\n", fdf.map.rotation[0]);
	printf("ROTATION Y -> %f\n", fdf.map.rotation[1]);
	init_map(&fdf);
	//printf("value of fdf->file:\n\n[%s]\n", fdf.file.temp);
	split_map(&fdf);
	set_points(&fdf);
	//printf("value of fdf->map.columns -> %d\n", fdf.map.columns);
	//printf("VALUE FDF->MAPS->ROWS -> %d\n", fdf.map.rows);
	transform_map(&fdf);

	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "Fil_De_Fer");
	fdf.img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel, &fdf.img.line_length,
								&fdf.img.endian);
	//draw_mesh(&fdf.img);
	draw_map(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
	mlx_hook(fdf.win, 2, 17, ft_close, &fdf);
	mlx_hook(fdf.win, 2, 1L<<0, key_hold, &fdf);
	//mlx_key_hook(fdf.win, key_up, &fdf);
	//mlx_hook(fdf.win, 2, 0, key_hold, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}

