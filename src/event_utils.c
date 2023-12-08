/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:21:35 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/08 00:18:15 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		key_up(int key, t_fdf *c)
{
	key == 53 ? exit(0) : 0;
	key == 49 ? init_map(c) : 0;
	key == 257 ? c->shft = 0 : 0;
	key == 48 ? c->mode *= -1 : 0;
	key == 8 ? c->color_on *= -1 : 0;
	if (key == 48 || key == 8)
		put_img_map(c);
	return (0);
}

int		key_hold(int key, t_fdf *c)
{
	t_map	*m;

	m = &c->map;
	key == 12 ? adjust_scale(c, -1) : 0;
	key == 14 ? adjust_scale(c, 1) : 0;
	key == 6 ? adjust_height(c, -0.1) : 0;
	key == 7 ? adjust_height(c, 0.1) : 0;
	key == 13 ? rotate_axis(c, &m->rotate_x, ROTATE_D) : 0;
	key == 1 ? rotate_axis(c, &m->rotate_x, -ROTATE_D) : 0;
	key == 0 ? rotate_axis(c, &m->rotate_y, -ROTATE_D) : 0;
	key == 2 ? rotate_axis(c, &m->rotate_y, ROTATE_D) : 0;
	key == 257 ? c->shft = 1 : 0;
	key == KEY_ARROW_UP && c->shft == 0 ? move_map(c, &m->move_y, -MV_PIXELS) : 0;
	key == KEY_ARROW_DOWN && c->shft == 0 ? move_map(c, &m->move_y, MV_PIXELS) : 0;
	key == KEY_ARROW_LEFT && c->shft == 0 ? move_map(c, &m->move_x, -MV_PIXELS) : 0;
	key == KEY_ARROW_RIGHT && c->shft == 0 ? move_map(c, &m->move_x, MV_PIXELS) : 0;
	key == KEY_ARROW_UP && c->shft == 1 ? move_map(c, &m->move_y, -MV_PIXELS * 5) : 0;
	key == KEY_ARROW_DOWN && c->shft == 1 ? move_map(c, &m->move_y, MV_PIXELS * 5) : 0;
	key == KEY_ARROW_LEFT && c->shft == 1 ? move_map(c, &m->move_x, -MV_PIXELS * 5) : 0;
	key == KEY_ARROW_RIGHT && c->shft == 1 ? move_map(c, &m->move_x, MV_PIXELS * 5) : 0;
	return (0);
}
