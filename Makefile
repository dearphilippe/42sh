# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/25 17:50:25 by ztisnes           #+#    #+#              #
#    Updated: 2018/03/30 21:52:26 by asarandi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 42sh
SRC			= main.c
OBJ			= $(SRC:%.c=%.o)
CC			= gcc
FLAGS		= -g -Wextra -Wall -Werror
INC			= -I libft/ -I ft_printf/
LIB			= -L libft/ -lft -L ft_printf/ -lftprintf -ltermcap

all:$(NAME)

$(NAME):
	make -C libft/
	make -C ft_printf/
	$(CC) $(FLAGS) $(INC) -c $(SRC)
	$(CC) $(FLAGS) $(LIB) $(OBJ) -o $(NAME)

rmobj:
	rm -f $(OBJ)

rmbin:
	rm -f $(NAME)

again: rmobj rmbin all

clean: rmobj
	make clean -C libft/
	make clean -C ft_printf/

fclean: clean rmbin
	make fclean -C libft/
	make fclean -C ft_printf/

re: fclean all
