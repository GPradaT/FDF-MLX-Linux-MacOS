/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:53:13 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/29 15:57:11 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	init(t_fdf fdf, t_vect *vect)
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
	sx = (fdf->img.width - 200) / fdf->map.columns;
	sy = (fdf->img.height - 200) / fdf->map.rows;
	if (sx < sy)
		fdf->map.scale = sx / 2;
	else
		fdf->map.scale = sy / 2;
	if(fdf->map.scale == 0)
		fdf->map.scale = 1;
}

float	set_theta(int degrees)
{
	float	radians;

	if(degrees == 0)
		return (0);
	radians = degrees * (M_PI / 100);
	return (radians);
}

void	set_color(t_vect *vect, t_map *map)
{
	int	max_z;
	int	z;

	z = vect->z * (map->z_height * map->scale);
	max_z = map->scale * map->max_z;
	if (z >= max_z * 1.5)
		vect->color = RED;
	else if (z >= max_z)
		vect->color = 0xFF9922;
	else if (max_z * 0.8 <= z && z < max_z)
		vect->color = 0x999922;
	else if (max_z * 0.6 <= z && z < max_z * 0.8)
		vect->color = GREEN;
	else if (max_z * 0.4 <= z && z < max_z * 0.6)
		vect->color = 0x229999;
	else if (max_z * 0.2 <= z && z < max_z * 0.4)
		vect->color = BLUE;
	else if (z < 0 && z < max_z * 0.2)
		vect->color = 0x222299;
	else if (z == 0)
		vect->color = WHITE;
	else
		vect->color = DARK_GREY;
}
