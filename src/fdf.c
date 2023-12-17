/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:06:27 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/17 16:12:34 by gprada-t         ###   ########.fr       */
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
	fdf->map.rotate_x = 5;
	fdf->map.rotate_y = 0;
	fdf->map.move_x = 0;
	fdf->map.move_y = 0;
	set_scale(fdf);
	fdf->map.center_x = (WIN_WIDTH - (fdf->map.columns * fdf->map.scale)) / 2;
	fdf->map.center_y = (WIN_HEIGHT - (fdf->map.rows * fdf->map.scale)) / 2;
	fdf->map.z_height = 1;
	put_img_map(fdf);
}
typedef struct s_vector2D {
    int x;
    int y;
} t_vector2D;

void project_vector(t_fdf *fdf) {
    t_vector2D projected_vector;

    // Cálculos de proyección (pueden variar según la lógica de proyección que desees)
    float focal_length = 50.0; // Longitud focal arbitraria (ajusta según sea necesario)
    projected_vector.x = (int)(fdf->map.vect->x * focal_length / fdf->map.vect->z) + WIN_WIDTH / 2;
    projected_vector.y = (int)(fdf->map.vect->y * focal_length / fdf->map.vect->z) + WIN_HEIGHT / 2;
    my_mlx_pixel_put(&fdf->img, projected_vector.x, projected_vector.y, 0xFFFFFF); // Puedes cambiar el color si lo deseas
}

// void draw_2D_vector(t_fdf *fdf) {

// 	t_vector2D projected_vector = project_vector(fdf);

//     // Dibuja el vector proyectado en la ventana
// }

void draw_lline(t_point p1, t_point p2, void *mlx_ptr, void *win_ptr) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float increment_x = (float)dx / (float)steps;
    float increment_y = (float)dy / (float)steps;

    float x = p1.x;
    float y = p1.y;

    int i = 0;
    while (i <= steps) {
        mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xFFFFFF); // Dibuja un píxel en el punto (x, y)
        x += increment_x + 2;
        y += increment_y + 2;
        i++;
    }
}
void draw_isometric(void *mlx_ptr, void *win_ptr) {
    t_point point1 = {100, 100};
    t_point point2 = {300, 100};
    t_point point3 = {200, 300};

    draw_lline(point1, point2, mlx_ptr, win_ptr);
    draw_lline(point2, point3, mlx_ptr, win_ptr);
    draw_lline(point3, point1, mlx_ptr, win_ptr);
}

int		main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		bad_use();
	fdf.file = argv[1];
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIN_WIDTH, WIN_HEIGHT, ">> GPradaT <<");
	fdf.img.width = WIN_WIDTH - OFF_X;
	fdf.img.height = WIN_HEIGHT - OFF_Y;
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
