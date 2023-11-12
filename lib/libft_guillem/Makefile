# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 05:47:38 by gprada-t          #+#    #+#              #
#    Updated: 2023/11/12 18:32:55 by gprada-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	libft.a

INCLUDE	=	libft.h

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I $(INCLUDE)

SRCS	= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
 		ft_strlen.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strlcpy.c \
		ft_strlcat.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_bzero.c \
		ft_calloc.c ft_strdup.c ft_atoi.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_strmapi.c ft_striteri.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ		= $(subst .c,.o,$(SRCS))
DEP		= $(addsuffix .d, $(basename$(OBJ)))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	ranlib $(NAME)

bonus: $(BONUS_OBJ) $(OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)
	ranlib $(NAME)
	@touch $@

%.o : %.c Makefile $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
