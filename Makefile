# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: passef <passef@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/25 17:50:25 by ztisnes           #+#    #+#              #
#    Updated: 2018/04/06 09:15:39 by passef           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		ft_printf/libftprintf.a
EXEC =		42sh

SRC =		libft/ft_putstr_fd.c \
			libft/ft_putchar_fd.c \
			libft/ft_putstr.c \

OBJ =		$(SRC:.c=.o)
CC =		gcc
FLAGS =		-g #-Wall -Wextra -Werror 
RM =		rm	-rf
LFT =		-C libft/
GREEN =		\033[92m
PURPLE =	\033[095m
YELLOW =	\033[093m
NORM =		\033[0m
CURSORUP =	\033[1A

all: $(NAME)
$(NAME): $(OBJ)
	@echo "$(PURPLE)[42sh] :$(NORM) $(GREEN)Creating Library$(NORM)";
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@$(CC) $(FLAGS) terms.c $(NAME) -o $(EXEC)
	@echo "$(PURPLE)[42sh] :$(NORM) $(GREEN)42sh Compiled!$(NORM)";
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@cd ft_printf && make re
	@echo "$(YELLOW)[PRINTF] :$(NORM) $(GREEN)Compiling $<$(NORM)";
clean:
	@$(RM) $(OBJ)
	@cd libft && make clean
	@echo "$(PURPLE)[42sh] :$(NORM) $(GREEN)Cleaning Object files $(NORM)";
fclean: clean
	@$(RM) $(NAME)
	@echo "$(PURPLE)[42sh] :$(NORM) $(GREEN)Cleaning 42sh $(NORM)";
re: fclean all
