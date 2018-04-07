#include "validate.h"

// TODO handle start with non CMD characters
t_queue *validate_lexer(t_queue *lex)
{
    t_queue *cpy;

    cpy = lex;
    while (lex && lex->type == SEP)
        lex = lex->next;
    if (lex && lex->type != CMD)
    {
        print_lexer_start_error(lex->name);
        free_queue(cpy);
        return (NULL);
    }
    return (lex);
}

// TODO implement method
t_queue     *validate_ast(t_queue *ast)
{
    return (ast);
}