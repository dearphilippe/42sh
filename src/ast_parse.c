/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:07:46 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 15:13:43 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_ast	*parse_lexer(char *str)
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
				return (NULL);
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
	if (!str || (*str != '\'' && *str != '"'))
		return (0);
	if (*str && *str == '\'')
		return (parse_quote_single(word, str));
	if (*str && *str == '"')
		return (parse_quote_double(word, str));
	return (0);
}

int		parse_quote_single(char **word, char *str)
{
	char	*cpy;
	int		res;
	int		i;

	res = 1;
	i = 0;
	cpy = str;
	if (!str || !*str || *str++ != '\'')
		return (0);
	if (str && *str && *str == '\'')
		return (++res);
	while (str && *str && ++res)
	{
		if (*str == '\'' && str[-1] != '\\')
			break ;
		str++;
	}
	if (!str || !*str || *str != '\'')
		return (0);
	++res;
	while (i++ < res)
	{
		if (!cpy)
			return (0);
		*word = ft_str_append(*word, *cpy++);
	}
	return (res);
}

int		parse_quote_double(char **word, char *str)
{
	char	*cpy;
	int		res;
	int		i;

	res = 1;
	i = 0;
	str = delete_backslash_in_double_quote(str);
	cpy = str;
	if (!str || !*str || *str++ != '"')
		return (0);
	if (str && *str && *str == '"')
		return (++res);
	while (str && *str && ++res)
	{
		if (*str == '"' && str[-1] != '\\')
			break ;
		str++;
	}
	if (!str || !*str || *str != '\"')
		return (0);
	++res;
	while (i++ < res)
	{
		if (!cpy)
			return (0);
		*word = ft_str_append(*word, *cpy++);
	}
	return (res);
}

t_ast	**parse_ast(t_ast **ast, t_ast *lex)
{
	int		i;

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

t_ast	*parse_tree(t_ast *lex)
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
		if (!lex || lex->type != CMD ||
				!(right = ast_new(lex->name, lex->type)))
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
