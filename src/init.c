/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:42:36 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/13 13:41:24 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	prepare(t_fdf fdf, t_vect *v)
{
	float	theta;
	int		x;
	int		y;
	int		z;

	x = v->x * fdf.map.scale;
	y = v->y * fdf.map.scale;
	z = v->z * (fdf.map.z_height * fdf.map.scale);
	fdf.color_on == 1 ? set_color(v, &fdf.map) : 0;
	theta = set_theta(fdf.map.rotate_y);
	v->x = x * cos(theta) - z * sin(theta);
	v->z = z * cos(theta) + x * sin(theta);
	theta = set_theta(fdf.map.rotate_x);
	v->y = y * cos(theta) - z * sin(theta);
	v->z = z * cos(theta) + y * sin(theta);
	v->x += fdf.map.move_x;
	v->y += fdf.map.move_y;
	v->x += fdf.map.center_x;
	v->y += fdf.map.center_y;
}

void	set_scale(t_fdf *fdf)
{
	int	sx;
	int	sy;

	fdf->map.scale = 0;
	sx = (fdf->img.width - 200) / fdf->map.columns;
	sy = (fdf->img.height - 200) / fdf->map.rows;
	if (sx < sy)
		fdf->map.scale = sx / 2;
	else
		fdf->map.scale = sy / 2;
	if (fdf->map.scale == 0)
		fdf->map.scale = 1;
}

float	set_theta(int degrees)
{
	float	radians;

	if (degrees == 0)
		return (0);
	radians = degrees * (M_PI / 180);
	return (radians);
}

void	set_color(t_vect *v, t_map *map)
{
	int	max_z;
	int	z;

	z = v->z * (map->z_height * map->scale);
	max_z = map->scale * map->max_z;
	if (z >- max_z * 1.5)
		v->color = RED;
	else if (z >= max_z)
		v->color = 0xFF9922;
	else if (max_z * 0.8 <= z && z < max_z)
		v->color = 0x999922;
	else if (max_z * 0.6 <= z && z < max_z * 0.8)
		v->color = GREEN;
	else if (max_z * 0.4 <= z && z < max_z * 0.6)
		v->color = 0x229999;
	else if (max_z * 0.2 <= z && z < max_z * 0.4)
		v->color = BLUE;
	else if (0 < z && z < max_z * 0.2)
		v->color = 0x222299;
	else if (z == 0)
		v->color = WHITE;
	else
		v->color = DARK_GREY;
}
