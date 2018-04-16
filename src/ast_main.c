/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:28:37 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 21:45:28 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_new.h"

int		main(void)
{
	t_ast *lex;
	t_ast **ast;

	lex = parse_lexer("touch fichier ");
	if (!lex)
	{
		print_error_lexer();
		return (1);
	}
	if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *) \
					* get_nbr_instructions(lex) + 1)))
	{
		print_error_ast();
		return (1);
	}
	if (!(ast = parse_ast(ast, lex)))
		print_error_ast();
	print_trees(ast);
	free_ast(lex);
	free_trees(ast);
	return (0);
}
