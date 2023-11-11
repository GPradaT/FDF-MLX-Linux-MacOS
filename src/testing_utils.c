/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/11 18:54:29 by gprada-t         ###   ########.fr       */
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
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x++, cord_y, color);
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x, cord_y++, color);
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x--, cord_y, color);
	for (i = 0; i < 200; i++)
		my_mlx_pixel_put(data, cord_x, cord_y--, color);
}

void	create_grid(t_data *data, int x, int y, int color)
{
	int	begin_x = 100;
	int	end_x = 1000;
	int	begin_y = 200;
	int	end_y = 1000;

	int	*grid_point = malloc(sizeof(int) * 2);

	while (begin_x + x < end_x + x)
	{
		grid_point[0] = begin_x;
		grid_point[1] = begin_y;
		my_mlx_pixel_put(data, grid_point[0], grid_point[1], color);
		begin_y = 100;
		while (begin_y + y < end_y + y)
		{
			grid_point[0] = begin_x;
			grid_point[1] = begin_y;
			my_mlx_pixel_put(data, grid_point[0], grid_point[1], color);
			begin_y += 5;
		}
		begin_x += 5;
	}
	free(grid_point);
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

