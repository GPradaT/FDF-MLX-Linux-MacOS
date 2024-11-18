#include "fdf.h"

void	matrix_identity(t_matrix *matrix)
{
	ft_memset(matrix, 0, sizeof(t_matrix));
	matrix->m[0][0] = 1;
	matrix->m[1][1] = 1;
	matrix->m[2][2] = 1;
	matrix->m[3][3] = 1;
}
