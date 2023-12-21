/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:42:36 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/21 05:04:32 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void rotateX(t_vect *point, float angle, int scale) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newY = point->y * cosA - point->z * sinA;
    float newZ = point->y * sinA + point->z * cosA;

    point->y = newY * scale * 0.2;
    point->z = newZ * scale * 0.2;
}

void rotateY(t_vect *point, float angle, int scale) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newX = point->x * cosA + point->z * sinA;
    float newZ = -point->x * sinA + point->z * cosA;

    point->x = newX * scale * 0.2;
    point->z = newZ * scale * 0.2;
}

void rotateZ(t_vect *point, float angle, int scale) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newX = point->x * cosA - point->y * sinA;
    float newY = point->y * sinA + point->y * cosA;

    point->x = newX * scale * 0.2;
    point->y = newY * scale * 0.2;
}

void		prepare3(t_fdf c, t_vect *v)
{
	float	theta;
	float	x;
	float	y;
	float	z;

	x = v->x * c.map.scale/2;
	y = v->y * c.map.scale/2;
	z = v->z * (c.map.z_height * c.map.scale);
	c.map.center_x = x + y + z;
	c.color_on == 1 ? set_color(v, &c.map) : 0;
	theta = set_theta(c.map.rotate_x);
	rotateX(v, theta, c.map.scale);
	theta = set_theta(c.map.rotate_z);
	rotateZ(v, theta, c.map.scale);
	theta = set_theta(c.map.rotate_y);
	rotateY(v, theta, c.map.scale);
	// v->x = x * cos(theta) - z * sin(theta);
	// v->z = z * cos(theta) + y * sin(theta);
	// v->y = y * cos(theta) - z * sin(theta);
	// v->z = z * cos(theta) + x * sin(theta);

	v->x += c.map.move_x;
	v->y += c.map.move_y;
	v->x += c.map.center_x;
	v->y += c.map.center_y;
	v->z += c.map.z_height;
}

void		prepare2(t_fdf c, t_vect *v)
{
	float	theta;
	int		x;
	int		y;
	int		z;

	x = v->x * c.map.scale;
	y = v->y * c.map.scale;
	z = v->z * (c.map.z_height * c.map.scale);
	c.color_on == 1 ? set_color(v, &c.map) : 0;
	theta = set_theta(c.map.rotate_y);
	v->x = x * cos(theta) - z * sin(theta);
	//v->z = z * cos(theta) + x * sin(theta);
	theta = set_theta(c.map.rotate_x);
	v->y = y * cos(theta) - z * sin(theta);
	v->z = z * cos(theta) + y * sin(theta);
	v->x += c.map.move_x;
	v->y += c.map.move_y;
	v->x += c.map.center_x;
	v->y += c.map.center_y;
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
	radians = degrees * (M_PI / 360);
	return (radians);
}

int	set_color(t_vect *v, t_map *map)
{
	int	max_z;
	int	z;

	z = v->z * (map->z_height * map->scale);
	max_z = map->scale * map->max_z;
	if (z >= max_z)
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
		v->color = BLUE;
	return (v->color);
}
