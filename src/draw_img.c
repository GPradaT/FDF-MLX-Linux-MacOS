/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:09:54 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/22 18:32:15 by gprada-t         ###   ########.fr       */
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

void	draw_grid(t_fdf *fdf, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
			mlx_pixel_put(fdf->mlx, fdf->win, (x += 20), y, color);
		y += 20;
	}
}

void	prepare_iso(t_fdf fdf, t_vect *v)
{
	float isometric_x, isometric_y;

    // Escalado de las coordenadas
    v->x = v->x * fdf.map.scale;
    v->y = v->y * fdf.map.scale;
    v->z = v->z * (fdf.map.z_height * fdf.map.scale);

    // Proyección isométrica
    isometric_x = v->x - v->y;
    isometric_y = (v->x + v->y) / 2 - v->z;

    // Otros ajustes si es necesario
    isometric_x += fdf.map.move_x;
    isometric_y += fdf.map.move_y;
    isometric_x += fdf.map.center_x;
    isometric_y += fdf.map.center_y;

    // Actualizar los valores del vector con la proyección isométrica
    v->y = isometric_y;
    v->x = isometric_x;

    // Puedes aplicar colores o realizar otras operaciones necesarias después de la proyección
    // fdf.color_on == 1 ? set_color(v, &fdf.map) : 0;
}

void	put_isometric(t_fdf *fdf)
{
	int		i;
	t_vect	vect;
	t_vect	down;

	clear_img(fdf);
	i = 0;
	draw_grid(fdf, 0x444444);
	while (i < (fdf->map.rows * fdf->map.columns))
	{
		vect = fdf->map.vect[i];
		prepare_iso(*fdf, &vect);
		if (i < (fdf->map.rows * fdf->map.columns) - fdf->map.columns)
		{
			down = fdf->map.vect[i + fdf->map.columns];
			prepare_iso(*fdf, &down);
			if (i < fdf->map.columns)
				ft_print_line(vect, down, fdf);
		}
		(i >= 0 && i % fdf->map.columns != 0) ? ft_print_line(fdf->map.prev, vect, fdf) : 0;
		fdf->map.prev = vect;
		i++;
	}
	if (fdf->mode)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, OFF_X, OFF_Y);
}

void	put_img_map(t_fdf *fdf)
{
	int		i;
	t_vect	vect;
	t_vect	down;


	clear_img(fdf);
	draw_grid(fdf, 0x444444);
	i = 0;
	while (i < (fdf->map.rows * fdf->map.columns))
	{
		vect = fdf->map.vect[i];
		prepare3(*fdf, &vect);
		if (i < (fdf->map.rows * fdf->map.columns) - fdf->map.columns)
		{
			down = fdf->map.vect[i + fdf->map.columns];
			prepare3(*fdf, &down);
			ft_print_line(vect, down, fdf);
		}
		if (i >= 0 && i % fdf->map.columns != 0)
			ft_print_line(fdf->map.prev, vect, fdf);
		fdf->map.prev = vect;
		i++;
	}
	if (fdf->mode)
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, OFF_X, OFF_Y);
}
