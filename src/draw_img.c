/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/08 12:14:29 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
		put_img_vector(fdf, start);
		if (start.x == end.x && start.y == end.y)
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
		init(*fdf, &vect);
		if (i < (fdf->map.rows * fdf->map.columns) - fdf->map.columns)
		{
			down = fdf->map.vect[i + fdf->map.columns];
			init(*fdf, &down);
			draw_line(fdf, vect, down);
			put_img_vector(fdf, down);
		}
		if (i > 0 && i % fdf->map.columns != 0)
			draw_line(fdf, fdf->map.prev, vect);
		put_img_vector(fdf, vect);
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
