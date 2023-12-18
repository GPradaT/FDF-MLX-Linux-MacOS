/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/18 23:27:46 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

#define ISO_ANGLE 30 // Ángulo de 30 grados en radianes

void	clear_img(t_fdf *fdf)
{
	if (fdf->mode == 1)
		ft_bzero(fdf->img.data, sizeof(int) * fdf->img.width * fdf->img.height);
	else
		mlx_clear_window(fdf->mlx, fdf->win);
}

void	put_img_vector(t_fdf *fdf, t_vect vect)
{
	int	i;

	///printf("hola\n");
	if (fdf->mode == 1)
	{
		 if (vect.x > fdf->img.width - 1 || vect.x < 1)
		 	return ;
		i = vect.x + (vect.y * fdf->img.width);
		 if (i > (fdf->img.width * fdf->img.height) || i < 0)
		 	return ;
		fdf->img.data[i] = vect.color;
	}
	else
		mlx_pixel_put(fdf->mlx, fdf->win, vect.x, vect.y, vect.color);
		// my_mlx_pixel_put(&fdf->img, vect.x, vect.y, 0x00ffff);
}

void drawLine(t_fdf *fdf, t_vect start, t_vect end)
{
	t_line	line;

	line.dx = abs(end.x - start.x);
    line.dy = abs(end.y - start.y);
    line.sx = (start.x < end.x) ? 1 : 0;
    line.sy = (start.y < end.y) ? 1 : 0;
    line.error = line.dx - line.dy;

	while ((start.x <= end.x) && (start.y <= end.y))
	{
		put_img_vector(fdf, start); // Draw a pixel
		if (start.x == end.x && start.y == end.y)
			break;
		line.e2 = 2 * line.error;
		if (line.e2 > line.dy)
		{
			line.error -= line.dy;
			start.x += line.sx;
		}
		if (line.e2 < line.dx)
		{
			line.error += line.dx;
			start.y += line.sy;
		}
	}
}

void	draw_grid(t_fdf *fdf, int color)
{
	for (size_t y = 0; y < WIN_HEIGHT; y += 15)
	{
		for (size_t x = 0; x < WIN_WIDTH; x += 15)
		{
			mlx_pixel_put(fdf->mlx, fdf->win, x, y, color);
			//fdf->img.data[(WIN_WIDTH * y) + x] = color;
			//color_buffer[(WIN_WIDTH * y) + x] = color;
			//fdf->img.data[(WIN_WIDTH * y) + x] = color_buffer[(WIN_WIDTH * y) + x];
		}
	}
}

void	put_img_map(t_fdf *fdf)
{
	int		i;
	t_vect	vect;
	//t_vect	vect2;
	t_vect	down;
	// t_point down2;
	// t_point vect2;
	// t_point prev2;

	clear_img(fdf);
	i = 0;
	draw_grid(fdf, 0x003333);
	while (i < (fdf->map.rows * fdf->map.columns))
	{
		vect = fdf->map.vect[i];
	//	vect = rotate_point_with_quaternion(vect, quaternion_rotation(vect, M_PI/4));
	//	prepare1(*fdf, &vect);
		prepare2(*fdf, &vect);
	//	prepare3(*fdf, &vect);
		//point->x = (previous_x - point->y) * cos(0.523599); // 0.523599 radianes es aproximadamente 30 grados en radianes
		//point->y = -point->z + (previous_x + point->y) * sin(0.523599); // sin(30) = 0.5

		//iso_projection(&vect, 2);
		if (i < (fdf->map.rows * fdf->map.columns) - fdf->map.columns)
		{
			down = fdf->map.vect[i + fdf->map.columns];
			prepare2(*fdf, &down);
			//drawLine(fdf, vect, down);
		//	prepare3(*fdf, &down);
		//	down = rotate_point_with_quaternion(down, quaternion_rotation(down, M_PI/4));
			//prepare1(*fdf, &down);
		//	iso_projection(vect); // Ajusta 'angle' según la rotación deseada
			drawLine(fdf, vect, down);
			//drawLine(fdf, vect2, down);
			//put_img_vector(fdf, down);
		}
		//printf("\n me quedare pillado aqui?? -> i = %d", i);
		(i > 0 && i % fdf->map.columns != 0) ? drawLine(fdf, fdf->map.prev, vect) : 0;
		//put_img_vector(fdf, vect);
		fdf->map.prev = vect;
		i++;
	}
	if (fdf->mode == 1)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, OFF_X, OFF_Y);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		rgb[4];

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = &img->data[(y * img->line_len) + (x * img->bpp)];
	rgb[0] = color & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = (color >> 16) & 0xFF;
	rgb[3] = color >> 24;
	pixel[0] = rgb[0];
	pixel[1] = rgb[1];
	pixel[2] = rgb[2];
	pixel[3] = rgb[3];
}

// void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	int	*dst;
// 	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
// 		return ;
// 	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
// 	*(unsigned int*)dst = color;
// }
/*
void	my_mlx_square(t_data *data, int color)
{
//	int		first_pixel = 1000;
//	int		last_pixel = 1000;

	float cord_x = 100;
	float cord_y = 100;
//	float cord_max_x = 1000;
//	float cord_max_y = 1000;

	int i;

	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x++, cord_y, color);
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x, cord_y++, color);
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x--, cord_y, color);
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x, cord_y--, color);
}


void	draw_line(t_data *data, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX = endX - beginX;
	double	deltaY = endY - beginY;

	double	pixelX = beginX;
	double	pixelY = beginY;

	int		pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	while (pixels)
	{
	    my_mlx_pixel_put(data, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	    --pixels;
	}
}
*/
