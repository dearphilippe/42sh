#include "parse.h"

/*
** TODO implement fonction
*/

void	free_ast(t_ast *head)
{
	head->name = NULL;
}

void	free_trees(t_ast **ast)
{
	while (ast && *ast)
	{
		free_ast(*ast);
		ast++;
	}
}
