/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:42:36 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/20 23:50:27 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void rotation_matrix(t_vect *v, t_fdf *fdf) {
    float ux = v->x;
    float uy = v->y;
    float uz = v->z;
    float cos_theta = cos(fdf->map.rotate_x);
    float sin_theta = sin(fdf->map.rotate_x);
    float one_minus_cos_theta = 100.0 - cos_theta;

    float matrix[3][3]; // Define tu matriz aquí, debería ser una matriz de 3x3

    matrix[0][0] = cos_theta + ux * ux * one_minus_cos_theta;
    matrix[0][1] = ux * uy * one_minus_cos_theta - uz * sin_theta;
    matrix[0][2] = ux * uz * one_minus_cos_theta + uy * sin_theta;

    matrix[1][0] = uy * ux * one_minus_cos_theta + uz * sin_theta;
    matrix[1][1] = cos_theta + uy * uy * one_minus_cos_theta;
    matrix[1][2] = uy * uz * one_minus_cos_theta - ux * sin_theta;

    matrix[2][0] = uz * ux * one_minus_cos_theta - uy * sin_theta;
    matrix[2][1] = uz * uy * one_minus_cos_theta + ux * sin_theta;
    matrix[2][2] = cos_theta + uz * uz * one_minus_cos_theta;

    // Aquí puedes hacer algo con la matriz de rotación si es necesario
	// float px = v->x;
    // float py = v->y;
    // float pz = v->z;


    // float rotated_x = matrix[0][0] * px + matrix[0][1] * py + matrix[0][2] * pz;//pz;
    // float rotated_y = matrix[1][0] * px + matrix[1][1] * py + matrix[1][2] * pz;//pz;
    // float rotated_z = matrix[2][0] * px + matrix[2][1] * py + matrix[2][2] * pz;

	// v->x = rotated_x;
	// v->y = rotated_y;
	// v->z = rotated_z;
}


//   float isometric_x, isometric_y;

//    // Escalado de las coordenadas
//    v->x = v->x * fdf.map.scale;
//    v->y = v->y * fdf.map.scale;
//    v->z = v->z * (fdf.map.z_height * fdf.map.scale);

//    // Proyección isométrica
//    isometric_x = v->x - v->y;
//    isometric_y = (v->x + v->y) / 2 - v->z;

//    // Otros ajustes si es necesario
//    isometric_x += fdf.map.move_x;
//    isometric_y += fdf.map.move_y;
//    isometric_x += fdf.map.center_x;
//    isometric_y += fdf.map.center_y;

//    // Actualizar los valores del vector con la proyección isométrica
//    v->x = isometric_x;
//    v->y = isometric_y;

//    // Puedes aplicar colores o realizar otras operaciones necesarias después de la proyección
//    fdf.color_on == 1 ? set_color(v, &fdf.map) : 0;

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

void rotateZ(t_vect *point, float angle) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newX = point->x * cosA - point->y * sinA;
    float newY = point->y * sinA + point->y * cosA;

    point->x = newX;// * scale/4;
    point->y = newY;// * scale/4;
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
	c.color_on == 1 ? set_color(v, &c.map) : 0;
	theta = set_theta(c.map.rotate_y);
	v->y = y * cos(theta) - z * sin(theta);
	theta = set_theta(c.map.rotate_x);
	v->x = x * cos(theta) - z * sin(theta);
	theta = set_theta(c.map.rotate_z);
	v->z = z * cos(theta) + -y * sin(theta);
	v->z = z * cos(theta) + x * sin(theta);
	// rotateY(v, theta, c.map.scale);
	// rotateX(v, theta, c.map.scale);
	// rotateZ(v, theta);

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
	//v->z = z * cos(theta) + y * sin(theta);
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
		v->color = RED;
	return (v->color);
}
