#include "parse.h"

t_ast	*validate_lexer(t_ast *lex)
{
	t_ast   *cpy;

	cpy = lex;
	while (lex)
	{
		if (!ft_strlen(lex->name) || lex->type != CMD)
			return (NULL);
		if ((lex = lex->next) && lex->type == CMD)
			return (NULL);
		lex = lex ? lex->next : lex;
	}
	return (cpy);
}

// TODO implement method
t_ast	*validate_ast(t_ast *ast)
{
	return (ast);
}
