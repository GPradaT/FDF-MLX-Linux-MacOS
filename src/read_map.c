/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:21:04 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/14 12:18:35 by gprada-t         ###   ########.fr       */
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
			return (printf("invallid value-> %d\n", *str),-1);
		str++;
	}
	return (0);
}

int	check_file(const char *str, t_fdf *fdf)
{
	int	fd;

	if (!str)
		return (EBADF);
	fd = open(str, O_RDONLY);
	char *buffer;
	char *line;
	buffer = get_next_line(fd);
	if (buffer)
	{
		line = get_next_line(fd);
		while (line)
		{
			buffer = ft_strjoin(buffer, line);
			line = get_next_line(fd);
		}
		fdf->file = buffer;
	}
	return (valid_charset(fdf->file));
}

void	set_points(t_fdf *fdf)
{
	int i = 0;
	while (fdf->file[i] && fdf->file[i] != '\n')
		i++;
	char *line = (char *)malloc(sizeof(char) * i + 1);
	ft_strlcpy(line, fdf->file, i - 1);
	line[i] = '\0';
//	printf("line->\t[\t%s\t]\t\n", line);

//	printf("\n\nDEBUG\n\n");
}
