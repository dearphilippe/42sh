/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:07:34 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 16:31:31 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "minishell.h"

int	ast_main3(void)
{
	t_ast	*lex;
	t_ast	**ast;
	char	*line;
	int		fd;

	fd = open("file", O_RDONLY);
	line = NULL;
	get_next_line(fd, &line);
	lex = parse_lexer(line);
	if (!lex)
	{
		print_error_lexer();
		return (1);
	}
	if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *) *
					get_nbr_instructions(lex) + 1)))
	{
		return (print_error_ast());
	}
	if (!(ast = parse_ast(ast, lex)))
		print_error_ast();
	print_trees(ast);
	free_ast(lex);
	free_trees(ast);
	return (0);
}
