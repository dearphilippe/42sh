#include "parse.h"

t_type		get_type(char *str)
{
	if (ft_strlen(str) == 1 && *str == ';')
		return (SEP);
	if (ft_strlen(str) == 1 && *str == '|')
		return (RED_PIPE);
	if (ft_strlen(str) == 2)
	{
		if (IS_OP_AND(str))
			return (OP_OR);
		if (IS_OP_AND(str))
			return (OP_AND);
		}
	return (CMD);
}

int			get_nbr_instructions(t_ast *lex)
{
	int	i;

	if (!lex)
	return (0);
	i = 1;
	while (lex)
	{
		if (lex->type == SEP)
			i++;
		lex = lex->next;
	}
	return (i);
}
