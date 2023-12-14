/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:56:32 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/13 08:57:49 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_axis(t_fdf *fdf, int *axis, int degrees)
{
	int d;

	d = *axis + degrees;
	if (d >= 360)
		*axis = 0;
	else if (d <= 0)
		*axis = 355;
	else
		*axis = d;
	put_img_map(fdf);
}

void	adjust_scale(t_fdf *fdf, int direction)
{
	int s;

	s = fdf->map.scale;
	if (direction > 0)
	{
		s++;
		if (s * fdf->map.rows > WIN_HEIGHT * 5)
			s--;
		if (s * fdf->map.columns > WIN_WIDTH * 5)
			s--;
	}
	else
		s--;
	if (s < 1)
		s = 1;
	if (fdf->map.scale != s)
	{
		fdf->map.scale = s;
		put_img_map(fdf);
	}
}

void	move_map(t_fdf *fdf, int *axis, int pixels)
{
	*axis += pixels;
	put_img_map(fdf);
}

void	adjust_height(t_fdf *fdf, float direction)
{
	fdf->map.z_height += direction;
	put_img_map(fdf);
}
