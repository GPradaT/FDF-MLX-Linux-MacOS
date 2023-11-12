/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:10:42 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/28 18:11:59 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*get_line_from(char *buffer);
char	*read_file(int fd, char *buffer);
char	*rest_buffer(char *buffer);
char	*ft_join_and_free(char *buffer, char *temp);
char	*ft_substr(char *str, unsigned int start, size_t len);
char	*ft_strchr(char *s, int c);
char	*free_buffer(char **buffer);
size_t	ft_strlen(const char *str);

#endif
