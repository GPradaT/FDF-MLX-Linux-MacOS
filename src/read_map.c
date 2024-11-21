/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:21:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/21 07:37:17 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	valid_charset(const char *str)
{
	while (*str)
	{
		if (!(ft_isspace(*str) || ft_ishexdigit(*str)) && *str != ',')
			return (printf("invallid value-> %d\n", *str), -1);
		str++;
	}
	return (0);
}

int	check_file(t_fdf *fdf)
{
	char	*buffer;
	char	*line;

	line = NULL;
	buffer = get_next_line(fdf->file.fd);
	if (buffer)
	{
		line = get_next_line(fdf->file.fd);
		while (line)
		{
			fdf->map.rows++;
			buffer = ft_strjoin(buffer, line);
			line = get_next_line(fdf->file.fd);
		}
		fdf->file.temp = buffer;
	}

	return (valid_charset(fdf->file.temp));
}

//#include <malloc/malloc.h>

int	pointer_count(void **pointer)
{
	void **temp;

	temp = pointer;
	int i = 0;
	while (temp[i])
		i++;
	return (i);
}



int	split_map(t_fdf *fdf)
{
	char **split_nl = ft_split(fdf->file.temp, '\n');
	char **split_line = ft_split(split_nl[0], ' ');
	fdf->map.columns = pointer_count((void **)split_line);
	fdf->map.rows = pointer_count((void **)split_nl);
	fdf->map.vect = (t_vect **)malloc(sizeof(t_vect *) * fdf->map.rows);
	fdf->map.vect_orig = (t_vect **)malloc(sizeof(t_vect *) * fdf->map.rows);
	if (!fdf->map.vect)
	{
		free_array((void **)split_nl);
		free_array((void **)split_line);
		return 0;
	}
	int i = -1;
	while (++i < fdf->map.rows)
	{
		fdf->map.vect[i] =  (t_vect *)malloc(sizeof(t_vect) * fdf->map.columns);
		fdf->map.vect_orig[i] =  (t_vect *)malloc(sizeof(t_vect) * fdf->map.columns);
		if (!fdf->map.vect[i])
		{
			while (--i >= 0)
				free(fdf->map.vect[i]);
			free(fdf->map.vect);
			free_array((void **)split_nl);
			free_array((void **)split_line);
			return 0;
		}
	}
	free_array((void **)split_line);
	free_array((void **)split_nl);
	return 0;
}

void	set_points(t_fdf *fdf)
{
	int		x;
	int		y;
	char	**split_nl;
	//t_vect	vect;

	split_nl = ft_split(fdf->file.temp, '\n');
	y = -1;
	while (++y < fdf->map.rows)
	{
		char **split_line = ft_split(split_nl[y], ' ');
		x = -1;
		while (++x < fdf->map.columns)
		{
			char **split_comma = ft_split(split_line[x], ',');
			fdf->map.vect_orig[y][x].x = (float)x;
			fdf->map.vect_orig[y][x].y = (float)y;
			fdf->map.vect_orig[y][x].z = (float)ft_atoi(split_comma[0]);
			fdf->map.vect_orig[y][x].color = split_comma[1] ? ft_atoi_base(split_comma[1] + 2, 16) : 0xFFFFFF;
			//fdf->map.vect_orig[y][x] = vect;
			free_array((void **)split_comma);
		}
	}
}

