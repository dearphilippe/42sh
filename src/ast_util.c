/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:10:27 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/22 02:36:06 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

int		ast_ambiguous_error(char *msg)
{
	ft_printf(STDERR_FILENO, msg);
	return (1);
}

int		ast_is_ambiguous(t_ast *ast)
{
	t_ast	*ptr;

	ptr = ast;
	while (ptr->next)
		ptr = ptr->next;
	ptr = ptr->parent;
	while ((ptr) && (ptr->parent))
	{
		if ((ptr->type == RED_PIPE) && (ptr->parent->type == RED_PREV))
			return (ast_ambiguous_error("Ambiguous input redirect.\n"));
		if ((ptr->type == RED_NEXT) && (ptr->parent->type == RED_PIPE))
			return (ast_ambiguous_error("Ambiguous output redirect.\n"));
		if ((ptr->type == RED_NNEXT) && (ptr->parent->type == RED_PIPE))
			return (ast_ambiguous_error("Ambiguous output redirect.\n"));
		ptr = ptr->parent;
	}
	return (0);
}

t_ast	**ast_create_tree(char *str)
{
	t_ast	*lex;
	t_ast	**ast;

	if ((lex = parse_lexer(delete_start_space(str))) == NULL)
	{
		ft_printf(STDERR_FILENO, "ast lexical error!\n");
		return (NULL);
	}
	if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *) *
					get_nbr_instructions(lex) + 1)))
	{
		free_ast(lex);
		ft_printf(STDERR_FILENO, "ast memory error!\n");
		return (NULL);
	}
	if (!(ast = parse_ast(ast, lex)))
	{
		free_ast(lex);
		free_trees(ast);
		ft_printf(STDERR_FILENO, "ast syntax error!\n");
		return (NULL);
	}
	free_ast(lex);
	return (ast);
}

void	init_parse_lexer(t_ast **lex, t_ast **node, char **word, char **term)
{
	*lex = NULL;
	*word = NULL;
	*term = NULL;
	*node = NULL;
}

int		parse_help(t_ast **lex, t_ast **node, char **word, char **term)
{
	char	*new_str;

	new_str = remove_start_space(*word);
	*node = ast_new(new_str, CMD);
	ft_strdel(&new_str);
	if (*node && !(*lex = ast_enqueue(*lex, *node)))
		return (0);
	ft_strdel(word);
	*word = 0;
	if (!(*lex = ast_enqueue(*lex, ast_new(*term, get_type(*term)))))
		return (0);
	return (1);
}
