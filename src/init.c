/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:42:36 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/19 02:14:11 by gprada-t         ###   ########.fr       */
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

    // float rotated_x = matrix[0][0] * px + matrix[0][1] * py + matrix[0][2] * pz;
    // float rotated_y = matrix[1][0] * px + matrix[1][1] * py + matrix[1][2] * pz;
    // float rotated_z = matrix[2][0] * px + matrix[2][1] * py + matrix[2][2] * pz;

	// v->x = rotated_x;
	// v->y = rotated_y;
}

t_quaternion quaternion_multiply(t_quaternion q1, t_quaternion q2) {
    t_quaternion result;
    result.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    result.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    result.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    return result;
}

t_quaternion quaternion_rotation(t_vect axis, float angle) {
    float sin_half_angle = sin(angle / 2.0);
    t_quaternion q;
    q.w = cos(angle / 2.0);
    q.x = axis.x * sin_half_angle;
    q.y = axis.y * sin_half_angle;
    q.z = axis.z * sin_half_angle;
    return q;
}

t_vect rotate_point_with_quaternion(t_vect point, t_quaternion rotation) {
    t_quaternion conjugate = {rotation.w, -rotation.x, -rotation.y, -rotation.z};
    t_quaternion p = {0, point.x, point.y, point.z};
    t_quaternion result = quaternion_multiply(rotation, quaternion_multiply(p, conjugate));
    t_vect rotated_point = {result.x, result.y, result.z, 0xff0000};
    return rotated_point;
}
void prepare(t_vect axis, float angle, t_vect *point_to_rotate) {
    float sin_half_angle = sin(angle / 2.0);
    t_quaternion rotation = { cos(angle / 2.0), axis.x * sin_half_angle, axis.y * sin_half_angle, axis.z * sin_half_angle };

    t_quaternion conjugate = { rotation.w, -rotation.x, -rotation.y, -rotation.z };
    t_quaternion p = { 0, point_to_rotate->x, point_to_rotate->y, point_to_rotate->z };
    t_quaternion result = quaternion_multiply(rotation, quaternion_multiply(p, conjugate));

    point_to_rotate->z = result.z;
    point_to_rotate->x = result.x;
    point_to_rotate->y = result.y;
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

    point->y = newY * scale;
    point->z = newZ * scale;
}

void rotateY(t_vect *point, float angle, int scale) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newX = point->x * cosA + point->z * sinA;
    float newZ = -point->x * sinA + point->z * cosA;

    point->x = newX * scale;
    point->z = newZ * scale;
}

void rotateZ(t_vect *point, float angle, int scale) {
    float cosA = cos(angle);
    float sinA = sin(angle);

    float newX = point->x * cosA - point->y * sinA;
    float newY = point->x * sinA + point->y * cosA;

    point->x = newX * 0.1 * scale;
    point->y = newY * 0.1 * scale;
}

void		prepare3(t_fdf c, t_vect *v)
{
	float	theta;
	//int		x;
	//int		y;
	//int		z;

	//x = v->x * c.map.scale;
	//y = v->y * c.map.scale;
	//z = v->z * (c.map.z_height * c.map.scale);
	c.color_on == 1 ? set_color(v, &c.map) : 0;
	theta = set_theta(c.map.rotate_y);
	rotateX(v, theta, c.map.scale);
	//rotateZ(v, theta, c.map.scale);
	theta = set_theta(c.map.rotate_x);
	rotateY(v, theta, c.map.scale);
//	rotateZ(v, theta);
//	rotateZ(v, theta);
	//v->x = x * cos(theta) - z * sin(theta);
	//v->z = z * cos(theta) + x * sin(theta);
	//v->y = y * cos(theta) - z * sin(theta);
	//v->z = z * cos(theta) + y * sin(theta);
	v->x += c.map.move_x;
	v->y += c.map.move_y;
	v->x += c.map.center_x;
	v->y += c.map.center_y;
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
	theta = set_theta(c.map.rotate_y*2*M_PI);
	v->x = x * cos(theta) - z * sin(theta);
//	v->z = z * cos(theta) + x * sin(theta);
	theta = set_theta(c.map.rotate_x);
	v->y = y * cos(theta) - z * sin(theta);
	v->z = z * cos(theta) + x * sin(theta);
	//v->z = z * cos(theta) + y * sin(theta);
	v->x += c.map.move_x;
	v->y += c.map.move_y;
	v->x += c.map.center_x;
	v->y += c.map.center_y;
}

void	prepare4(t_fdf fdf, t_vect *v) {
//    float theta;
  //  int x, y;

    v->x = v->x * fdf.map.scale;
    v->y = v->y * fdf.map.scale;
    v->z = v->z * (fdf.map.z_height * fdf.map.scale);
    fdf.color_on == 1 ? set_color(v, &fdf.map) : 0;
	//printf("\n-- vector x, y, (%d.%d), vector z (%d)", fdf.map.vect->x, fdf.map.vect->y, fdf.map.vect->z);

    rotation_matrix(v, &fdf);
	v->x += fdf.map.move_x;
	v->y += fdf.map.move_y;
	v->x += fdf.map.center_x;
	v->y += fdf.map.center_y;
}
    // Resto del código para preparar los vectores...
//// // }
//void	prepare2(t_fdf fdf, t_vect *v)
//{
//	float	theta;
//	int		x;
//	int		y;
//	int		z;

//	x = v->x * fdf.map.scale;
//	y = v->y * fdf.map.scale;
//	z = v->z * (fdf.map.z_height * fdf.map.scale);
//	fdf.color_on == 1 ? set_color(v, &fdf.map) : 0;


//	theta = set_theta(45);
//	v->x = x * cos(theta) - z * sin(theta);
//	v->z = z * cos(theta) + x * sin(theta);
//	theta = set_theta(45);
//	v->y = y * cos(theta) - z * sin(theta);
//	v->z = z * cos(theta) + y * sin(theta);
//	v->x += fdf.map.move_x;
//	v->y += fdf.map.move_y;
//	v->x += fdf.map.center_x;
//	v->y += fdf.map.center_y;
//	// printf("\n-- vector x, y, (%d.%d), vector z (%d)", v->x, v->y, v->z);
//	// printf("\n-- vector x, y, (%d.%d), vector z (%d)", x, y, z);
//}

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
		v->color = RED;
}
