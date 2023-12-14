/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/14 18:09:10 by gprada-t         ###   ########.fr       */
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
		mlx_pixel_put(fdf->mlx, fdf->win, vect.x, vect.y, 0x00ffff);
		// my_mlx_pixel_put(&fdf->img, vect.x, vect.y, 0x00ffff);
}

void drawLine(t_fdf *fdf, t_vect start, t_vect end)
{
	t_line	line;

	line.dx = labs(end.x - start.x);
    line.dy = labs(end.y - start.y);
    line.sx = (start.x < end.x) ? 1 : -1;
    line.sy = (start.y < end.y) ? 1 : -1;
    line.error = line.dx - line.dy;

	while ((start.x <= end.x) && (start.y <= end.y))
	{
		printf("\n| pre_pixel_put\n|start.x = %d|\n|start.y = %d|\ncolor %x\n",
		start.x, start.y, start.color);
		printf("\n| pre_pixel_put\n|end.x = %d|\n|end.y = %d|\ncolor %x\n",
		end.x, end.y, end.color);
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
/*
void	draw_line(t_fdf *fdf, t_vect start, t_vect end)
{
	t_line	line;

	line.dx = labs(end.x - start.x);
	if (start.x < end.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = labs(end.y - start.y);
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
}*/

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
		//	printf("\n| después del drawLine |\n");
			put_img_vector(fdf, down);
		//	printf("\n| después del put_img_vector |\n");
		}
		(i > 0 && i % fdf->map.columns != 0) ? drawLine(fdf, fdf->map.prev, vect) : 0;
		//printf("\n| antes del put_img_vector 2 |\n");
		put_img_vector(fdf, vect);
		//printf("\n| después del put_img_vector 2 |\n");
		printf("veces que pinto => %d\n", i);
		fdf->map.prev = vect;
		i++;
	}
	if (fdf->mode == 1)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, OFF_X, OFF_Y);
	//put_menu(fdf->mlx, fdf->win, fdf);
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
