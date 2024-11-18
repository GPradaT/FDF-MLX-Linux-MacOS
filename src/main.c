/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:20:09 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/18 15:52:15 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

void	draw_mesh(t_data *img)
{
	//X will go --
	//Y will go |
	int x = 0;
	int y = 0;

	int distance_points = 15;

	while (y < MAX_HEIGHT)
	{
		x = 0;
		while (x < MAX_WIDTH)
			my_mlx_pixel_put(img, x++, y, 0x00FF0000);
		y += distance_points;
	}
	x = 0;
	while (x < MAX_WIDTH)
	{
		y = 0;
		while (y < MAX_HEIGHT)
			my_mlx_pixel_put(img, x, y++, 0x00FF0050);
		x += distance_points;
	}

}

int	main(int argc, char **argv)
{
	if (argc != 2 || (ft_strlen(argv[1]) < 4
		|| ft_strncmp(".fdf", &argv[1][ft_strlen(argv[1]) - 4], 4)))
	{
		errno = 2;
		perror("wrong input, what are you trying...?");
		return (errno);
	}

	t_fdf	fdf;
	fdf.file.fd = open(argv[1], O_RDONLY);
	if (fdf.file.fd <= 0)
	{
		errno = EBADF;
		return (errno);
	}
	check_file(&fdf);
	printf("value of fdf->file:\n\n[%s]\n", fdf.file.temp);
	split_map(&fdf);
	set_points(&fdf);
	printf("value of fdf->map.columns -> %d\n", fdf.map.columns);
	printf("VALUE FDF->MAPS->ROWS -> %d\n", fdf.map.rows);

/*	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Fil_De_Fer");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	draw_mesh(&img);

	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);*/
	return (0);
}

