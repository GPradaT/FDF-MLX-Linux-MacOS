/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/14 14:51:06 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
		i = vect.x + ((vect.y) * fdf->img.width);
		if (i > (fdf->img.width * fdf->img.height) || i < 0)
			return ;
		fdf->img.data[i] = vect.color;
	}
	else
		mlx_pixel_put(fdf->mlx, fdf->win, vect.x, vect.y, vect.color);
}

void drawLine(t_fdf *fdf, t_vect start, t_vect end) {
    int dx = labs(end.x - start.x);
    int dy = labs(end.y - start.y);
    int sx = (start.x < end.x) ? 1 : -1;
    int sy = (start.y < end.y) ? 1 : -1;
    int err = dx - dy;

	while (start.x <= end.x && start.y <= end.y)
	{
		printf("\n| pre_pixel_put, start.x = %d start.y = %d|\n", start.x, start.y);
		mlx_pixel_put(fdf->mlx, fdf->win, start.x, start.y, 0xFFFFFF); // Draw a pixel
		if (start.x == end.x && start.y == end.y)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}
void	draw_line(t_fdf *fdf, t_vect start, t_vect end)
{
	t_line	line;

	line.dx = ft_absolute(end.x - start.x);
	if (start.x < end.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = ft_absolute(end.y - start.y);
	if (start.y < end.y)
		line.sy = 1;
	else
		line.sy = -1;
	if (line.dx > line.dy)
		line.error = line.dx / 2;
	else
		line.error = -line.dy / 2;
	while (1)
	{
		printf("holaPutIMG\n");
		my_mlx_pixel_put(&fdf->img, start.x, start.y, 0xFFFFFF);
		if (start.x == end.x || start.y == end.y)
			break ;
		line.e2 = line.error;
		if (line.e2 > -line.dx)
		{
			line.error -= line.dy;
			start.x += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.error += line.dx;
			start.y += line.sy;
		}
	}
}

void	put_img_map(t_fdf *fdf)
{
	int		i;
	t_vect	vect;
	t_vect	down;

	clear_img(fdf);
	i = 0;
	while (i < (fdf->map.rows * fdf->map.columns))
	{
		vect = fdf->map.vect[i];
		prepare(*fdf, &vect);
		if (i < (fdf->map.rows * fdf->map.columns) - fdf->map.columns)
		{
			down = fdf->map.vect[i + fdf->map.columns];
			prepare(*fdf, &down);
			drawLine(fdf, vect, down);
			printf("\n| después del drawLine |\n");
			put_img_vector(fdf, down);
			printf("\n| después del put_img_vector |\n");
		}
		(i > 0 && i % fdf->map.columns != 0) ? drawLine(fdf, fdf->map.prev, vect) : 0;
		printf("\n| antes del put_img_vector 2 |\n");
		put_img_vector(fdf, vect);
		printf("\n| después del put_img_vector 2 |\n");
		fdf->map.prev = vect;
		i++;
	}
	if (fdf->mode == 1)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, OFF_X, OFF_Y);
	//put_menu(fdf->mlx, fdf->win, fdf);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int	*dst;
	printf("hola_pixelput\n");
	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
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
