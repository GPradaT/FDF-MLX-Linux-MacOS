/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:21:35 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/24 10:49:52 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
	else if (key == ESC_KEY) //ESC
		ft_close(fdf);
	else
		return (0);
	transform_map(fdf);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_HEIGHT, WIN_WIDTH);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,\
			&fdf->img.line_length, &fdf->img.endian);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	return (0);
}
