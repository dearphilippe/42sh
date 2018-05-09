# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: passef <passef@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/15 23:17:54 by passef            #+#    #+#              #
#    Updated: 2018/05/09 05:24:38 by asarandi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 42sh
SRCFILES =	ast.c \
	ast_free.c \
	ast_get.c \
	ast_helper.c \
	ast_parse.c \
	ast_print.c \
	ast_util.c \
	ast_validate.c \
	ast_parse_quote.c \
	parse_autocomplet.c \
	autocomplete.c \
	builtin_cd.c \
	builtin_help.c \
	builtin_localvar.c \
	builtins.c \
	builtins_env.c \
	char_array.c \
	child_argv.c \
	error.c \
	exec.c \
	file_op.c \
	group_process.c \
	header.c \
	history.c \
	history_keys.c \
	init.c \
	input_a.c \
	input_b.c \
	input_c.c \
	kv_array.c \
	main.c \
	path_utils.c \
	pipes.c \
	process.c \
	redirects.c \
	quotes.c \
	signal.c \
	special_keys_a.c \
	special_keys_a_2.c \
	special_keys_b.c \
	string_utils.c \
	tab_columns.c \
	tab_columns_f.c \
	tab_files.c \
	tab_files_2.c \
	tab_files_help.c \
	tab_key.c \
	tab_key2.c \
	tab_key3.c \
	tab_utils.c \
	termcaps.c \

OBJFILES	= $(SRCFILES:%.c=%.o)
SRC			= $(addprefix src/,$(SRCFILES))
OBJ			= $(addprefix obj/,$(OBJFILES))
CC			= gcc
FLAGS		= -O2 -Wextra -Wall -Werror
INC			= -I libft/inc -I inc/
LIB			= -L libft/ -lft -ltermcap

all:$(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

objdir:
	mkdir -p obj/

obj/%.o: src/%.c | objdir
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

rmobj:
	rm -rf obj/

rmbin:
	rm -rf $(NAME)

again: rmobj rmbin all

ast:
	make -C libft/
	gcc -o ASTDEMO src/ast*.c -L libft/ -l ft -I libft/inc

clean: rmobj
	make clean -C libft/

fclean: clean rmbin
	make fclean -C libft/

re: fclean all
