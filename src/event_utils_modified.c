/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils_modified.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:21:35 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/23 14:22:33 by gprada-t         ###   ########.fr       */
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

int key_hold(int keycode, t_fdf *fdf)
{
    float angle = 0.05f; // Ajusta este valor según la velocidad de rotación que desees

    if (keycode == 2) // D
        update_rotation(fdf, 0.0f, 1.0f, 0.0f, angle);
    else if (keycode == 13) // W
        update_rotation(fdf, 0.0f, 1.0f, 0.0f, -angle);
    else if (keycode == 1) // S
        update_rotation(fdf, 1.0f, 0.0f, 0.0f, angle);
    else if (keycode == 0) // A
        update_rotation(fdf, 1.0f, 0.0f, 0.0f, -angle);
    else if (keycode == 65307) // Tecla Esc para salir
        ft_close(keycode, fdf);
    else
        return (0); // Si no es una tecla que nos interese, no hacemos nada

    // Después de actualizar la rotación, transformamos y dibujamos el mapa de nuevo
    transform_map(fdf);
    // Limpiamos la imagen antes de volver a dibujar
    mlx_clear_window(fdf->mlx, fdf->win);
    mlx_destroy_image(fdf->mlx, fdf->img.img);
    fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
    fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, &fdf->img.line_length, &fdf->img.endian);

    draw_map(fdf);
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);

    return (0);
}

//int key_hold(int key, t_fdf *fdf)
//{
//    if (!fdf || !fdf->mlx || !fdf->win)
//        return (0);

//    // Actualizar rotaciones/traslaciones
//    if (key == 13) fdf->map.rotation[0] += 0.5;  // W
//    if (key == 1) fdf->map.rotation[0] -= 0.5;   // S
//    if (key == 0) fdf->map.rotation[1] += 0.5;   // A
//    if (key == 2) fdf->map.rotation[1] -= 0.5;   // D

//	if (key == 126) fdf->map.translation[1] -= 10; // UP
//	if (key == 125) fdf->map.translation[1] += 10; // DOWN
//	if (key == 123) fdf->map.translation[0] -= 10; // LEFT
//	if (key == 124) fdf->map.translation[0] += 10; // RIGHT

//	if (key == 9) fdf->map.scale += 0.1; // V
//	if (key == 10) fdf->map.scale -= 0.1; // -


//    // Limpiar imagen anterior
//    ft_memset(fdf->img.addr, 0, fdf->img.line_length * 1080);

//    // Crear nueva imagen
//    //mlx_destroy_image(fdf->mlx, fdf->img.img);
//    //fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
//    //fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
//    //                                 &fdf->img.line_length, &fdf->img.endian);

//    // Actualizar y redibujar
//    transform_map(fdf);
//    draw_map(fdf);

//    // Actualizar ventana
//    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);

//    return (0);
//}
