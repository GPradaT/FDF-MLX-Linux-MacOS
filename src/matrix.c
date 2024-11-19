#include "fdf.h"

void	matrix_identity(t_matrix *matrix)
{
	ft_memset(matrix, 0, sizeof(t_matrix));
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}

void	matrix_rotation(t_matrix *matrix, float alpha_x, float alpha_y, float alpha_z)
{
	matrix_identity(matrix);

	alpha_x = 35.264f * M_PI / 180;
	alpha_y = 45.0f * M_PI / 180;
	alpha_z = 0.0f;

	if (alpha_x)
	{
		matrix->m[1][1] = cos(alpha_x);
		matrix->m[1][2] = -sin(alpha_x);
		matrix->m[2][1] = sin(alpha_x);
		matrix->m[2][2] = cos(alpha_x);
	}
	if (alpha_y)
	{
		matrix->m[0][0] = cos(alpha_y);
		matrix->m[0][2] = sin(alpha_y);
		matrix->m[2][0] = -sin(alpha_y);
		matrix->m[2][2] = cos(alpha_y);
	}
	if (alpha_z)
	{
		matrix->m[0][0] = cos(alpha_z);
		matrix->m[0][1] = -sin(alpha_z);
		matrix->m[1][0] = sin(alpha_z);
		matrix->m[1][1] = cos(alpha_z);
	}
}

void	matrix_translation(t_matrix *matrix, float tx, float ty, float tz)
{
	matrix_identity(matrix);
	matrix->m[0][3] = tx;
	matrix->m[1][3] = ty;
	matrix->m[2][3] = tz;
}

void	matrix_scale(t_matrix *matrix, float sx, float sy, float sz)
{
	matrix_identity(matrix);
	matrix->m[0][0] = sx;
	matrix->m[1][1] = sy;
	matrix->m[2][2] = sz;
}

void	matrix_multiply(t_matrix *result, t_matrix *m1, t_matrix *m2)
{
    t_matrix temp;
    int i, j, k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp.m[i][j] = 0;
            for (k = 0; k < 4; k++) {
                temp.m[i][j] += m1->m[i][k] * m2->m[k][j];
            }
        }
    }
    *result = temp;
}

void init_transform_matrix(t_matrix *matrix, float rot[3], float scale[3], float trans[3])
{
    t_matrix rot_matrix, scale_matrix, trans_matrix, temp;

    matrix_rotation(&rot_matrix, rot[0], rot[1], rot[2]);
    matrix_scale(&scale_matrix, scale[0], scale[1], scale[2]);
    matrix_translation(&trans_matrix, trans[0], trans[1], trans[2]);

    // Multiplicar matrices en orden: translación * rotación * escala
    matrix_multiply(&temp, &trans_matrix, &rot_matrix);
    matrix_multiply(matrix, &temp, &scale_matrix);
}
