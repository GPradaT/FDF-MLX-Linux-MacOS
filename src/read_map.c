/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 22:11:14 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/12 13:29:15 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_map	reading_map(int fd)
{
	char	**map;
	char	*line;
	int		i, j;

	i = 0;
	j = 0;
	while (line)
	{
		ft_printf("%s\n", line);
		line = get_next_line(fd);
	}
}

int main()
{
	int fd = open("../maps/10-2.fdf");

	reading_map(fd);
}
