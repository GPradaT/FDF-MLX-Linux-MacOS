/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:20:09 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/23 14:18:52 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
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

t_quaternion	quaternion_from_axis_angle(float x, float y, float z, float angle)
{
	t_quaternion q;

	float sin_half_angle = sin(angle / 2.0f);
	float cos_half_angle = cos(angle / 2.0f);

	q.w = cos_half_angle;
	q.x = x * sin_half_angle;
	q.y = y * sin_half_angle;
	q.z = z * sin_half_angle;

	return q;
}

t_quaternion	quaternion_multiply(t_quaternion q1, t_quaternion q2)
{
	t_quaternion result;

	result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

	return result;
}

t_vect		rotate_vector(t_vect v, t_quaternion q)
{
	t_quaternion p = {0, v.x, v.y, v.z};
	t_quaternion q_conj = {q.w, -q.x, -q.y, -q.z};

	t_quaternion result = quaternion_multiply(quaternion_multiply(q, p), q_conj);

	t_vect rotated;
	rotated.x = result.x;
	rotated.y = result.y;
	rotated.z = result.z;
	rotated.color = v.color;

	return rotated;
}

void transform_map(t_fdf *fdf)
{
    int x, y;

    // Aplicar transformación a cada punto
    for (y = 0; y < fdf->map.rows; y++)
    {
        for (x = 0; x < fdf->map.columns; x++)
        {
            // Copiar el vector original
            t_vect v = fdf->map.vect_orig[y][x];

            // Aplicar rotación usando cuaterniones
            v = rotate_vector(v, fdf->q);

            // Aplicar escala
            v.x *= fdf->map.scale;
            v.y *= fdf->map.scale;
            v.z *= fdf->map.scale;

            // Aplicar traslación para centrar en pantalla
            v.x += (WIN_WIDTH / 2) + fdf->map.translation[0];
            v.y += (WIN_HEIGHT / 2) + fdf->map.translation[1];

            // Guardar el vector transformado
            fdf->map.vect[y][x] = v;
        }
    }
}
//void transform_map(t_fdf *fdf)
//{
//    int x, y;
//    t_matrix transform;

//	float rotation_x = fdf->map.rotation[0];
//	printf("ROTATION X -> %f\n", rotation_x);
//	float rotations[3] = {fdf->map.rotation[0] * M_PI / 180.0, fdf->map.rotation[1] * M_PI / 180.0, 0}; // Ángulos X,Y,Z
//    float scales[3] = {30.0, 30.0, 30.0};  // Factor de escala
//    //float rotations[3] = {fdf->map.rotation[0] * M_PI / 180.0, fdf->map.rotation[1] * M_PI / 180.0, fdf->map.rotation[2]}; // Ángulos X,Y,Z
//    //float scales[3] = {fdf->map.scale, fdf->map.scale, fdf->map.scale};  // Factor de	 escala
//    float translations[3] = {(MAX_WIDTH / 2) + fdf->map.translation[0], (MAX_HEIGHT / 2) + fdf->map.translation[1], 0};  // Centrar en pantalla

//    // Inicializar matriz de transformación
//    init_transform_matrix(&transform, rotations, scales, translations);

//	// Aplicar transformación a cada punto
//	y = -1;
//	while (++y < fdf->map.rows)
//	{
//		x = -1;
//		while (++x < fdf->map.columns)
//		{
//			t_vect *v = &fdf->map.vect_orig[y][x];

//			*v = rotate_vector(*v, fdf->q);
//			//float px = fdf->map.vect_orig[y][x].x;
//			//float py = fdf->map.vect_orig[y][x].y;
//			//float pz = fdf->map.vect_orig[y][x].z;

//			//// Aplicar transformación
//			//fdf->map.vect[y][x].x = transform.m[0][0] * px + transform.m[0][1] * py
//			//						+ transform.m[0][2] * pz + transform.m[0][3];
//			//fdf->map.vect[y][x].y = transform.m[1][0] * px + transform.m[1][1] * py
//			//						+ transform.m[1][2] * pz + transform.m[1][3];
//			//fdf->map.vect[y][x].z = transform.m[2][0] * px + transform.m[2][1] * py
//			//						+ transform.m[2][2] * pz + transform.m[2][3];
//			printf("value of fdf->map.vect[y][x].x -> %f\n", fdf->map.vect[y][x].x);
//			printf("value of fdf->map.vect[y][x].y -> %f\n", fdf->map.vect[y][x].y);
//			printf("value of fdf->map.vect[y][x].z -> %f\n", fdf->map.vect[y][x].z);
//        }
//    }
//}

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
						0x00FF0000);
			if (y < fdf->map.rows - 1)
				draw_line(&fdf->img, fdf->map.vect[y][x].x, fdf->map.vect[y][x].y,
						fdf->map.vect[y + 1][x].x, fdf->map.vect[y + 1][x].y,
						0x00FF0000);
			x++;
		}
		y++;
	}

}

int ft_close(int keycode, t_fdf *fdf)
{
	(void)keycode;
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit (0);
}

void init_map(t_fdf *fdf)
{
    printf("Iniciando mapa en: %p\n", (void*)fdf);
    ft_memset(&fdf->map, 0, sizeof(t_map));
    fdf->map.scale = 20.0f;
    fdf->map.rotation[0] = 35.0f;
    fdf->map.rotation[1] = 45.0f;
    fdf->map.translation[0] = 0;
    fdf->map.translation[1] = 0;
	fdf->q.w = 1.0f;
	fdf->q.x = 0.0f;
	fdf->q.y = 0.0f;
	fdf->q.z = 0.0f;
}

void	normalize_quaternion(t_quaternion *q)
{
	float norm = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);

	q->w /= norm;
	q->x /= norm;
	q->y /= norm;
	q->z /= norm;
}

void	update_rotation(t_fdf *fdf, float axis_x, float axis_y, float axis_z, float angle)
{
	t_quaternion delta = quaternion_from_axis_angle(axis_x, axis_y, axis_z, angle);
	fdf->q = quaternion_multiply(delta, fdf->q);
	normalize_quaternion(&fdf->q);
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
	//mlx_hook(fdf.win, 2, 0, ft_close, &fdf);
	mlx_hook(fdf.win, 2, 0, key_hold, &fdf);
	//mlx_key_hook(fdf.win, key_up, &fdf);
	//mlx_hook(fdf.win, 2, 0, key_hold, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}

