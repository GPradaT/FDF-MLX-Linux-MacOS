/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 20:50:40 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
/*
t_map	create_map(t_map *map, char **read_map)
{
	int distance_point = 10;
	int start_x = 0;
	int start_y = 0;
	int x = 0;
	int	y = 0;
	map->start_p.x = start_x;
	map->start_p.y = start_y;
	//------------------------------set end point --------------------//
	while (read_map[x])
	{
		while (read_map[x][y])
			y += distance_point;
		x += distance_point;
	}
	map->end_p.x = 1920;
	map->end_p.y = 1080;
	x = 0;
	y = 0;

	if (**read_map)
		map = malloc(sizeof(t_map) * sizeof(read_map));
	while (read_map[x])
	{

		while (read_map[x][y])
		{
			map->y = read_map[x][y];
			map->y += distance_point;
			y += distance_point;
		}
		map->x += distance_point;
		x += distance_point;
	}
	return (*map);
}

void	create_grid(t_fdf *fdf, int color)
{
	int begin_y = fdf->map.start_p.y;

	while (fdf->map.x < fdf->map.end_p.x)
	{
		fdf->map.y = begin_y;
		my_mlx_pixel_put(fdf->data, fdf->map.x, fdf->map.y, color);
		while (fdf->map.y < fdf->map.end_p.y)
		{
			my_mlx_pixel_put(fdf->data, fdf->map.x, fdf->map.y, color);
			fdf->map.y += 5;
		}
		fdf->map.x += 5;
	}
}
*/
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

