/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 03:53:24 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 03:57:56 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/*
** Don't send space at the end of the string
*/

t_ast		*parse_lexer(char *str)
{
	t_ast	*lex;
	t_ast	*node;
	char	*word;
	char	*term;
	int		res;

	lex = NULL;
	word = NULL;
	term = NULL;
	while (str && *str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (!(res = parse_quote(&word, str)))
			{
				return (NULL);
			}
			str += res;
			continue ;
		}
		else if (*str && *str != ' ' && (term = get_type_string(str)))
		{
			node = ast_new(remove_start_space(word), CMD);
			if (node && !(lex = ast_enqueue(lex, node)))
				return (NULL);
			ft_strdel(&word);
			word = NULL;
			if (!(lex = ast_enqueue(lex, ast_new(term, get_type(term)))))
				return (NULL);
			str += ft_strlen(term);
			ft_strdel(&term);
			term = NULL;
			continue ;
		}
		word = ft_str_append(word, *str++);
	}
	if (ft_strlen(word))
	{
		node = ast_new(remove_start_space(word), CMD);
		if (node && !(lex = ast_enqueue(lex, node)))
			return (NULL);
		ft_strdel(&word);
		word = NULL;
	}
	return (validate_lexer(lex));
}

int		parse_quote(char **word, char *str)
{
	int	res;
	int	i;

	i = 0;
	if (!str || (*str != '\'' && *str != '"'))
		return (0);
	if (*str && *str == '\'' && !(res = parse_quote_single(str)))
		return (0);
	if (*str && *str == '"' && !(res = parse_quote_double(str)))
		return (0);
	while (i++ < res)
	{
		if (!str)
			return (0);
		*word = ft_str_append(*word, *str++);
	}
	return (res);
}

int		parse_quote_single(char *str)
{
	int	i;

    i = 1;
	if (!str || !*str || *str++ != '\'')
		return (0);
	while (str && *str && *str != '\'' && ++i)
		str++;
	if (str && *str == '\'')
		return (++i);
	return (0);
}

int		parse_quote_double(char *str)
{
	int	i;

	i = 1;
	if (!str || !*str || *str++ != '"')
		return (0);
	if (str && *str && *str == '"')
		return (++i);
	while (str && *str && str[0] != '"' && str[-1] != '\\' && ++i)
		str++;
	if (str && str[0] == '"' && str[-1] != '\\')
		return (++i);
	return (0);
}

t_as	**parse_ast(t_ast **ast, t_ast *lex)
{
	int	i;

	i = 0;
	ast[i] = NULL;
	while (lex)
	{
		if (lex->type == SEP)
			ast[++i] = NULL;
		else if (!(ast[i] = ast_enqueue(ast[i], ast_new(lex->name, lex->type))))
			return (NULL);
		lex = lex->next;
	}
	ast[++i] = 0;
	i = 0;
	while (ast[i])
	{
		if (!(ast[i] = parse_tree(ast[i])))
			return (NULL);
		i++;
	}
	return (ast);
}

t_ast		*parse_tree(t_ast *lex)
{
	t_ast	*ast;
	t_ast	*op;
	t_ast	*right;
	t_ast	*cpy;

	if (!lex || lex->type != CMD || !(ast = ast_new(lex->name, lex->type)))
		return (NULL);
	cpy = lex;
	lex = lex->next;
	while (lex)
	{
		if (lex->type == CMD || !(op = ast_new(lex->name, lex->type)))
			return (NULL);
		lex = lex->next;
		if (!lex || lex->type != CMD || !(right = ast_new(lex->name, lex->type)))
			return (NULL);
		op->next = ast;
		op->right = right;
		right->parent = op;
		ast->parent = op;
		ast = op;
		lex = lex->next;
	}
	free_ast(cpy);
	return (validate_ast(ast));
}
