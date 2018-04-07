#include "print.h"

void	print_queue(t_queue *node)
{
    while (node)
    {
        ft_putstr(node->name);
       /* ft_putstr(" [");
        ft_putnbr(node->type);
        ft_putstr("]");*/
        ft_putstr("\n");
        node = node->next;
    }
}

void	print_lexer_start_error(char *name)
{
    ft_putstr("parse error near '");
    ft_putstr(name);
    ft_putstr("\n");
}

void	print_error_lexer(void)
{

}

void	print_error_ast(void)
{

}