/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_minilibx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:59:41 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 14:41:04 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

int	main(void)
{
/*	t_fdf	fdf;
	t_data	img;
	int x, y;

	x = 100;
	y = 100;
	
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "Hello world!");
	
	img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
*/	
	int fd = open("./src/42.fdf", O_RDONLY);
	char	*line;

	line = get_next_line(fd);
	
	printf("%d", fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);



/*
	my_mlx_square(&img, 0x00FF00);
	

	mlx_put_image_to_window(fdf.mlx, fdf.win, img.img, 0, 0);
	mlx_loop(fdf.mlx);*/
	return (0);
} 
