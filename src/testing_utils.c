/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/11 17:53:37 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_map	my_map()
{
	t_map	map;

	map.point.x = 100;
	map.point.y = 200;

	return (map);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_square(t_data *data, int color)
{
//	int		first_pixel = 1000;
//	int		last_pixel = 1000;
	
	float cord_x = 100;
	float cord_y = 100;
//	float cord_max_x = 1000;
//	float cord_max_y = 1000;
	
	int i;
	//int count;
	while(cord_x < 1000 && cord_y < 1000)
	{
		for (i = 0; i < 200; i++)
			my_mlx_pixel_put(data, cord_x++, cord_y++, color);
		for (i = 0; i < 200; i++)
			my_mlx_pixel_put(data, cord_x, cord_y--, color);
		for (i = 0; i < 200; i++)
			my_mlx_pixel_put(data, cord_x--, cord_y, color);

	}
}

/*void	my_draw_line(t_data *data, int beginX, int beginY, int endX, int endY, int color)
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
}*/

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

