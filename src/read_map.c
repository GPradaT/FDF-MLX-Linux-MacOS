/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:11:14 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/29 10:51:15 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	init_map(t_fdf	*fdf)
{
	fdf->map.rotate_x = 5;
	fdf->map.rotate_y = 0;
	fdf->map.move_x = 0;
	fdf->map.move_y = 0;
	set_scala(fdf);
	fdf->map.center_x = (WIN_WIDTH / 2);
	fdf->map.center_y = (WIN_HEIHT / 2);
	fdf->map.z_height = 1;
	put_img_map(fdf);
}

void	read_file(t_fdf *fdf, t_file *file)
{
	char	*file_buffer;
	int		i;
	if_error(file->fd = open(fdf->file, O_RDONLY), "File");
	file->contents = malloc(1);
	while (file->eof = read(file->fd, &file->buffer, BUFFER_SIZE))
	{
		file->buffer[file->eof] = '\0';
		file->contents = ft_join_and_free_gnl(file->contents, file->buffer);
	}
	file->split_y = ft_split(file->contents, '\n');
	file->split_x = ft_split(file->split_y[0], ' ');
	i = 0;
	while(file->split_x[i])
		free(split_x[i++]);
	fdf->map.columns = i;
	i = 0;
	while (file->split_y[i])
		i++;
	fdf->map.rows = = i;
	free(file->contents);
	free(file->split_x);
}

void	set_vectors(t_fdf *fdf, t_iterators *iter, t_file *file)
{
	char **z_values;

	z_values = ft_split(file->split_x[iter->x], ',');
	fdf->map.vect[iter->i].x = iter->x;
	fdf->map.vect[iter->i].y = iter->y;
	fdf->map.vect[iter->i].z = ft_atoi_base(file->split_x[iter->x], 10);
	if (fdf->map.vect[iter->i].z > fdf->map.max_z)
		fdf->map.max_z = fdf->map.vect[iter->i].z;
	if (z_values[1])
		fdf->map.vect[iter->i].color = ft_atoi_base(z_values[1])
	else
	{
		if (fdf->map.vect[iter->i].z == 0)
			fdf->map.vect[iter->i].color = GREEN;
		else
			fdf->map.vect[iter->i].color = BLUE;
	}
	free_array((void **)z_values);
}

void	set_map(t_fdf *fdf)
{
	t_file	file;

	read_file(fdf, &file);
	create_map(fdf, &file);
	init_map(fdf);
}

void	create_map(t_fdf *fdf, t_file *file)
{
	t_iterators iter;

	fdf->map.vect = malloc(sizeof(t_vect) * (fdf->map.row * fdf->map.columns));
	fdf->map.vect.z = 0;
	iter.i = 0;
	iter.y = 0;
	while (file->split_y[iter.y])
	{
		iter.x = 0;
		file->split_x = ft_split(file->split_y[iter.y], ' ');
		while (file->split_x[iter.x])
		{
			if (iter.x >= fdf->map.columns)
				break ;
			set_vector(fdf, &iter, file);
			free(file->split_x[iter.x++]);
		}
		if (iter.x < fdf->map.columns)
			if_error(0, "map error.....");
		free(file->split_x);
		iter.y++;
	}
	free_array((void  **)file->split_y);
}
