#include "parse.h"

// TODO handle start with non CMD characters
t_ast *validate_lexer(t_ast *lex)
{
    t_ast *cpy;

    cpy = lex;
    while (lex && lex->type == SEP)
        lex = lex->next;
    if (lex && lex->type != CMD)
    {
        print_lexer_start_error(lex->name);
        free_ast(cpy);
        return (NULL);
    }
    return (lex);
}

// TODO implement method
t_ast     *validate_ast(t_ast *ast)
{
    return (ast);
}