#include "free.h"

// TODO implement fonction
void	free_queue(t_queue *head)
{

}

void	free_ast(t_queue **ast)
{
    while (ast && *ast)
    {
        free_queue(*ast);
        ast++;
    }
}