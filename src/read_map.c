/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:21:04 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/20 22:30:12 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	read_file(t_fdf *fdf, t_file *file)
{
	int	i;

	check_error((file->fd = open(fdf->file, O_RDONLY)), "FILE");
	printf("hola");
	file->contents = malloc(1);
	while ((file->eof = read(file->fd, &file->buffer, BUFF_SIZE)))
	{
		file->buffer[file->eof] = '\0';
		file->temp = file->contents;
		file->contents = ft_strjoin(file->temp, file->buffer);
		free(file->temp);
	}
	file->split_y = ft_split(file->contents, '\n');
	file->split_x = ft_split(file->split_y[0], ' ');
	i = 0;
	while (file->split_x[i])
		free(file->split_x[i++]);
	fdf->map.columns = i;
	i = 0;
	while ((file->split_y[i++]));
	fdf->map.rows = i;
	free(file->contents);
	free(file->split_x);
}

void	set_vector(t_fdf *fdf, t_iter *iter, t_file *file)
{
	char	**val;

	val = ft_split(file->split_x[iter->x], ',');
	fdf->map.vect[iter->i].x = iter->x;
	fdf->map.vect[iter->i].y = iter->y;
	fdf->map.vect[iter->i].z = ft_atoi(file->split_x[iter->x]);
	//fdf->map.vect[iter->i].z = ft_atoi_base(file->split_x[iter->x], 10);
	// printf("\n| -- Z = %d --", fdf->map.vect[iter->i].z);
	//if (fdf->map.vect[iter->i].z > fdf->map.max_z)
	//	fdf->map.max_z = fdf->map.vect[iter->i].z;
	if (val[1])
		fdf->map.vect[iter->i].color = ft_atoi_base(val[1] + 2, 16);
	else
	{
		if (fdf->map.vect[iter->i].z == 0)
			set_color(&fdf->map.vect[iter->i], &fdf->map);
		else
		//	set_color(&fdf->map.vect[iter->i], &fdf->map);
			fdf->map.vect[iter->i].color = GREEN;
	}
	free_array((void **)val);
}

void	create_map(t_fdf *fdf, t_file *file)
{
	t_iter	iter;

	fdf->map.vect = malloc(sizeof(t_vect) * (fdf->map.rows *fdf->map.columns));
	fdf->map.max_z = 0;
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
			iter.i++;
		}
		if (iter.x < fdf->map.columns)
			check_error(0, " creating map bad row sizes");
		free(file->split_x);
		iter.y++;
	}
	free_array((void **)file->split_y);
}

void	set_map(t_fdf *fdf)
{
	t_file	file;

	read_file(fdf, &file);
	create_map(fdf, &file);
	init_map(fdf);
}

void	free_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
