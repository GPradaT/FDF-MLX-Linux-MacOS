/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:13 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/29 14:02:16 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	init(t_fdf fdf, t_vect vect)
{
	float	theta;
	int		x;
	int		y;
	int		z;

	x = vect->x * fdf.map.scale;
	y = vect->y * fdf.map.scale;
	z = vect->z * (fdf.map.z_height * fdf.map.scale);
	if (fdf.color_on == 1)
		set_color(vect, &fdf.map);
	theta = set_theta(fdf.map.rotate_y);
	vect->x = x * cos(theta) - z * sin(theta);
	vect->z = z * cos(theta) + x * sin(theta);
	theta = set_theta(fdf.map.rotate_x);
	vect->y = y * cos(theta) - z * sin(theta);
	vect->z = z * cos(theta) + y * sin(theta);
	vect->x += fdf.map.move_x;
	vect->y += fdf.map.move_y;
	vect->x += fdf.map.center_x;
	vect->y += fdf.map.center_y;
}

void	set_scale(t_fdf *fdf)
{
	int	sx;
	int	sy;

	fdf->map.scale = 0;
	///continue
}
