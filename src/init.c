/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 07:42:36 by gprada-t          #+#    #+#             */
/*   Updated: 2024/11/18 10:05:09 by gprada-t         ###   ########.fr       */
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

void	init(t_fdf	*fdf)
{
	fdf->map.vect = NULL;
	fdf->map.scale = 1;
	fdf->map.rows = 0;
	fdf->map.columns = 0;
	fdf->file.fd = 0;
	fdf->file.eof = 0;
	fdf->file.contents = NULL;
	fdf->file.temp = NULL;
	fdf->file.split_y = NULL;
	fdf->file.split_x = NULL;
}
