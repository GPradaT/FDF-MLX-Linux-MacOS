/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:21:35 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/24 11:40:56 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	key_hold(int key, t_fdf *fdf)
{
	float	angle;

	angle = 0.05f;
	if (key == D_KEY)
		update_rotation(fdf, 0.0f, 1.0f, 0.0f, angle);
	else if (key == W_KEY)
		update_rotation(fdf, 0.0f, 1.0f, 0.0f, -angle);
	else if (key == A_KEY)
		update_rotation(fdf, 1.0f, 0.0f, 0.0f, angle);
	else if (key == S_KEY)
		update_rotation(fdf, 1.0f, 0.0f, 0.0f, -angle);
	else if (key == E_KEY)
		update_rotation(fdf, 0.0f, 0.0f, 1.0f, angle);
	else if (key == R_KEY)
		update_rotation(fdf, 0.0f, 0.0f, 1.0f, -angle);
	else if (key == LEFT_KEY)
		fdf->map.translation[0] -= 10.0f;
	else if (key == RIGHT_KEY)
		fdf->map.translation[0] += 10.0f;
	else if (key == UP_KEY)
		fdf->map.translation[1] -= 10.0f;
	else if (key == DOWN_KEY)
		fdf->map.translation[1] += 10.0f;
	else if (key == V_KEY)
		fdf->map.scale += 1.0f;
	else if (key == B_KEY)
		fdf->map.scale -= 1.0f;
	else if (key == ESC_KEY)
		ft_close(fdf);
	else
		return (0);
	transform_map(fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,\
			&fdf->img.line_length, &fdf->img.endian);
	draw_mesh(&fdf->img);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
