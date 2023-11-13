# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/14 21:59:38 by gprada-t          #+#    #+#              #
#    Updated: 2023/11/13 13:56:25 by gprada-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
COLOR	= \033[1;39m
GREEN	= \033[1;32m
BLUE	= \033[1;34m
#------------------------------------>NAME<------------------------------------#
NAME	=	libftprintf.a

#----------------------------------->HEADER<-----------------------------------#
HEADER	=	ft_printf.h
LIB_H	=	../libft_guillem/

#------------                     LIBFT     ;;;;;;;;================           #
LIB		=	../libft_guillem/libft.a

#------------------------------------->SRC<----–-------------------------------#
SRCS	=	ft_printf.c ft_print_str.c ft_put_numbers.c ft_print_pointer.c
OBJ_DIR	=	./objs/
OBJ		=	$(addprefix $(OBJ_DIR), $(subst .c,.o,$(SRCS)))
DEP		=	$(addsuffix .d, $(basename$(OBJ)))
# ----------------------           COMMANDS                ------------------- #
INCLUDE	=	-I$(HEADER) -I$(LIB_H)
CC		= 	cc
CFLAGS	= 	-Wall -Wextra -Werror
MDP		=	mkdir -p
#                       ------------ RU2LES --------------                     #
$(OBJ_DIR)%.o:%.c Makefile $(HEADER) $(LIB)
	@$(MDP) $(dir $@)
	@printf "$(GREEN)	\rCompiling --> $(BLUE)$<   $(COLOR)		\r"
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP $(INCLUDE) -c $< -o $@

all:
	@echo ""
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	@cp $(LIB) $(NAME)
	@ar crs $(NAME) $(OBJ)
	@printf "\n$(GREEN) $(basename $(NAME)) created successfully.$(COLOR)"

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@make clean
	@rm -rf $(NAME)
	@printf "\n$(GREEN) $(basename $(NAME)) removed successfully.$(COLOR)"

re: fclean all
	@printf "\n$(GREEN) $(basename $(NAME)) remade successfully.$(COLOR)"

.PHONY: all clean fclean re

-include $(DEP)
