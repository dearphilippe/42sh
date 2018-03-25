# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/03 09:23:03 by brabo-hi          #+#    #+#              #
#    Updated: 2018/02/11 19:27:27 by brabo-hi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
SRC=\
	ft_get.c\
	ft_helper.c\
	ft_liste.c\
	ft_ls.c\
	ft_print.c\
	ft_sort.c\
	ft_utils.c\
	main.c
FLAGS=-Wextra -Wall -Werror -g
LIBFT=./libft
LIBFTPRINTF=./ft_printf
LIBFT_NAME=libft.a

all:$(NAME)

$(NAME):
	@cd $(LIBFT) && make
	@cd $(LIBFTPRINTF) && make
	@gcc -c $(SRC) $(FLAGS)
	@gcc $(SRC:.c=.o) -o $(NAME) libft/libft.a ft_printf/libftprintf.a

clean:
	@cd $(LIBFT) && make clean
	@cd $(LIBFTPRINTF) && make clean
	@/bin/rm -f $(SRC:.c=.o)

fclean: clean
	@cd $(LIBFT) && make fclean
	@cd $(LIBFTPRINTF) && make fclean
	@/bin/rm -f $(NAME)

re: fclean all
	@cd $(LIBFT) && make re
	@cd $(LIBFTPRINTF) && make re
