

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:06:27 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/22 17:00:24 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void	bad_use(void)
{
	ft_putstr("\nUse => ./FdF <url/file/directory.fdf>\n");
	exit (0);
}

void	check_error(int error, char *message)
{
	if (error < 1)
	{
		ft_printf("- Error: %s\n", message);
		exit(1);
	}
}

void	init_map(t_fdf *fdf)
{
	fdf->map.center_x = (WIN_WIDTH - (fdf->map.columns * fdf->map.scale)) / 2;
	fdf->map.center_y = (WIN_HEIGHT - (fdf->map.rows * fdf->map.scale)) / 2;
	fdf->map.rotate_x = 0;
	fdf->map.rotate_y = 0;
	fdf->map.rotate_z = 0;
	fdf->map.move_x = 0;
	fdf->map.move_y = 0;
	set_scale(fdf);
	fdf->map.z_height = 1;
	// put_isometric(fdf);
	put_img_map(fdf);
}


float	ft_module(float x, float y)
{
	float	mod;

	mod = sqrt((x * x) + (y * y));
	return (mod);
}

int	ft_valid_point(t_vect p)
{
	if (p.x < 0 || p.x >= WIN_WIDTH || p.y < 0 || p.y >= WIN_HEIGHT)
		return (0);
	return (1);
}
void	ft_print_line(t_vect a, t_vect b, t_fdf *design)
{
	t_vect	c;
	t_vect	inc;
	float	hip;
	float	len;

	if (!ft_valid_point(a) || !ft_valid_point(b))
		 	return ;
	hip = ft_module(b.x - a.x, b.y - a.y);
	c = a;
	len = hip;
	inc.x = (b.x - a.x) / hip;
	inc.y = (b.y - a.y) / hip;
	while (len > 0)
	{
		if (ft_valid_point(c))
			mlx_pixel_put(design->mlx, design->win, c.x, c.y, 0x0ff0f0);
		c.x += inc.x;
		c.y += inc.y;
		len--;
	}
}
// void	ft_print_line(t_vect a, t_vect b, t_fdf *design)
// {
// 	t_vect	c;
// 	t_vect	inc;
// 	float	hip;
// 	float	len;

// 	// if (!ft_valid_point(a) || !ft_valid_point(b))
// 	// 	 	return ;
// 	hip = ft_module(b.x - a.x, b.y - a.y);
// 	c = a;
// 	len = hip;
// 	inc.x = (b.x - a.x) / hip;
// 	inc.y = (b.y - a.y) / hip;
// 	while (len > 0  /*&& hip < 10 * design->map.scale*/)
// 	{
// 			// if (ft_valid_point(c))
// 				// mlx_pixel_put(design->mlx, design->win, c.x, c.y,  0x00ff00);
// 			// else
// 				mlx_pixel_put(design->mlx, design->win, c.x + 1, c.y + 1, (set_color(&c, &design->map) << 2));
// 				// my_mlx_pixel_put(&design->img, c.x, c.y, 250);
// 		c.x += inc.x;
// 		c.y += inc.y;
// 		len--;
// 	}
// 	// mlx_put_image_to_window(design->mlx, design->win, design->img.img, 0, 0);

// }

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		bad_use();
	fdf.file = argv[1];
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIN_WIDTH, WIN_HEIGHT, ">> GPradaT <<");
	fdf.img.width = WIN_WIDTH;
	fdf.img.height = WIN_HEIGHT;
	fdf.img.img = mlx_new_image(fdf.mlx, fdf.img.width, fdf.img.height);
	fdf.img.data = mlx_get_data_addr(fdf.img.img, &fdf.img.bpp,
					&fdf.img.line_len, &fdf.img.endian);
	fdf.shft = 0;
	fdf.mode = 0;
	fdf.color_on = -1;
	set_map(&fdf);
    // draw_isometric(fdf.mlx, fdf.win);
    mlx_hook(fdf.win, 2, 0, key_hold, &fdf);
	mlx_key_hook(fdf.win, key_up, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
