/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 02:45:37 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/04/22 02:45:39 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int		ast_main(void)
{
	t_ast *lex;
	t_ast **ast;

	lex = parse_lexer("touch file && echo \"hello\" ; ls -la");
	if (!lex)
	{
		print_error_lexer();
		return (1);
	}
	if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *)
					* get_nbr_instructions(lex) + 1)))
	{
		print_error_ast();
		return (1);
	}
	if (!(ast = parse_ast(ast, lex)))
		print_error_ast();
	free_ast(lex);
	print_trees(ast);
	free_trees(ast);
	free(ast);
	return (0);
}
