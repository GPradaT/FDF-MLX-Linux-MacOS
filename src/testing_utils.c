/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/09 13:38:36 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_map	my_map()
{
	t_map	map;

	map.point.x = 10;
	map.point.y = 20;

	return (map);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_square(t_data *data, t_map map, int color)
{
	int		first_pixel = 1000;
	int		last_pixel = 1000;
	
	while (map.point.y < first_pixel)
		my_mlx_pixel_put(data, map.point.y++, (WIN_HEIGHT - last_pixel), color);
	while (map.point.x < last_pixel)
		my_mlx_pixel_put(data, map.point.x++, (WIN_WIDTH - first_pixel), color);
}

void	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX = endX - beginX;
	double	deltaY = endY - beginY;

	double	pixelX = beginX;
	double	pixelY = beginY;
	
	int		pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	while (pixels)
	{
	    mlx_pixel_put(mlx, win, pixelX, pixelY, color);
	    pixelX += deltaX;
	    pixelY += deltaY;
	    --pixels;
	}
}

void	draw_square(t_fdf fdf)
{
	int a, b, c, d;

	a = 100;
	b = 100;
	c = 500;
	d = 500;
	
	while (a++ < c)
		draw_line(fdf.mlx, fdf.win, a, b, c, b, 0x001FD5);
	while (b++ < 500)
		draw_line(fdf.mlx, fdf.win, a, b, c, d, 0xB9D500);
	a = 100;
	b = 100;
	while (a < 500)
		draw_line(fdf.mlx, fdf.win, a++, b, c, b, 0xFFFFF0);
	while (c > 100)
		draw_line(fdf.mlx, fdf.win, b, c--, a, d, 0xFF0000);
	while(b < 500)
		draw_line(fdf.mlx, fdf.win, b++, a, c, d, 0xFF00F0);
	while (d > 100)
		draw_line(fdf.mlx, fdf.win, c, b, a, d--, 0x00FFD9);
}
