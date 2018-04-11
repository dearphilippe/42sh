#include "parse.h"

// TODO implement fonction
void	free_ast(t_ast *head)
{
	head->name[0] += 0;
}

void	free_trees(t_ast **ast)
{
    while (ast && *ast)
    {
        free_ast(*ast);
        ast++;
    }
}
