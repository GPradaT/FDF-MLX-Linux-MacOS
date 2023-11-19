/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:11:14 by gprada-t          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	reading_map(int fd)
{
	char	**map;
	char	*line;
	int		i, j;

	i = 0;
	j = 0;
	while (line)
	{
		//		ft_printf("%s\n", line);
		line = get_next_line(fd);
		ft_putstr(line);
	}
}

t_map	create_map(char *str)
{
	int		fd;
	t_map	map;

	fd = open(str, O_RDONLY);
	map_parsing(fd);
	valid_map(map);
	return (map);
}
