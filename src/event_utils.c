/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:21:35 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/21 09:21:49 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


#define KEY_V 9 // Define KEY_V with an appropriate value


int		key_up(int key, t_fdf *c)
{
	(void)c;
	key == 53 ? exit(0) : 0;
	//key == 49 ? init_map(c) : 0;
	//key == 257 ? c->shft = 0 : 0;
	//key == 48 ? c->mode *= -1 : 0;
	//key == 8 ? c->col/or_on *= -1 : 0;
	//key == KEY_T ? put_isometric(c) : 0;
	//if (key == 48 || key == 8)
	//	put_img_map(c);
	return (0);
}
int key_hold(int key, t_fdf *fdf)
{
    if (!fdf || !fdf->mlx || !fdf->win)
        return (0);
    if (key == ESC_KEY)
	exit(0);
    // Actualizar rotaciones/traslaciones
    if (key == W_KEY) fdf->map.rotation[0] += 0.5;  // W
    if (key == S_KEY) fdf->map.rotation[0] -= 0.5;   // S
    if (key == A_KEY) fdf->map.rotation[1] += 0.5;   // A
    if (key == D_KEY) fdf->map.rotation[1] -= 0.5;
    if (key == E_KEY) fdf->map.rotation[2] += 0.5;
    if (key == R_KEY) fdf->map.rotation[2] -= 0.5;
	if (key == 126) fdf->map.translation[1] -= 10; // UP
	if (key == 125) fdf->map.translation[1] += 10; // DOWN
	if (key == LEFT_KEY) fdf->map.translation[0] -= 10; // LEFT
	if (key == RIGHT_KEY) fdf->map.translation[0] += 10; // RIGHT

	if (key == B_KEY) fdf->map.scale += 0.5; // +
	if (key == V_KEY) fdf->map.scale -= 0.5; // -
	
	if (key == P_KEY)
	{
		for (int i = 0; i < fdf->map.rows; i++)
		{
			for (int j = 0; j < fdf->map.columns; j++)
			{
				if (fdf->map.vect_orig[i][j].z != 0)
					fdf->map.vect_orig[i][j].z += 1;
			}
		}
	}


    // Limpiar imagen anterior
    ft_memset(fdf->img.addr, 0, fdf->img.line_length * 1080);

    // Crear nueva imagen
    mlx_destroy_image(fdf->mlx, fdf->img.img);
    fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
    fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
                                     &fdf->img.line_length, &fdf->img.endian);

    // Actualizar y redibujar
    transform_map(fdf);
    draw_map(fdf);

    // Actualizar ventana
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);

    return (0);
}
