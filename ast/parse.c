#include "parse.h"

/*
**	Don't send space at the end of the string
*/

t_ast		*parse_lexer(char *str)
{
	t_ast	*lex;
	char	*word;
	char	*term;
	t_ast	*node;

	lex = NULL;
	word = NULL;
	term = NULL;
	while (str && *str)
	{
		if (*str == '\'' || *str == '"')
		{
			str += parse_quote(&word, str);
			continue ;
		}
		if (*str && (*str == '|' || *str == '&' || *str == ';') && /
		 	(term = contain_term(str)))
		{
			node = ast_new(remove_start_space(word), CMD);
			if (node && !(lex = ast_enast(lex, node)))
				return (NULL);
			ft_strdel(&word);
			word = NULL;
			if (!(lex = ast_enast(lex, ast_new(term, get_type(term)))))
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
		if (node && !(lex = ast_enast(lex, node)))
			return (NULL);
		ft_strdel(&word);
		word = NULL;
	}
	return (validate_lexer(lex));
}

int			parse_quote(char **word, char *str)
{
	int		i;

	i = 1;
	if (*str == '\'' && str++)
	{
		if (str && *str && *str == '\'' && ++i)
			return (i);
		*word = ft_str_append(*word, '\'');
		while (str && *str && ++i && *str != '\'')
			*word = ft_str_append(*word, *str++);
		if (str && *str == '\'' && ++i)
			*word = ft_str_append(*word, '\'');
		}
		else if (*str == '"' && str++)
		{
		if (str && *str && *str == '"' && ++i)
			return (i);
		*word = ft_str_append(*word, '"');
		while (str && str[0] && str[0] == '"' && str[-1] != '\\' && ++i)
			*word = ft_str_append(*word, *str++);
		if (str && *str == '"' && ++i)
			*word = ft_str_append(*word, '"');
	}
	return (i);
}

t_ast		**parse_ast(t_ast **ast, t_ast *lex)
{
	int		i;

	i = 0;
	ast[i] = NULL;
	while (lex)
	{
		if (lex->type == SEP)
			ast[++i] = NULL;
		else if (!(ast[i] = ast_enast(ast[i], ast_new(lex->name, lex->type))))
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
		if (!lex || lex->type != CMD || /
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
