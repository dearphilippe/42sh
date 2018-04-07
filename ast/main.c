#include "main.h"

int     main(int argc, char **argv)
{
    t_queue *lex;
    t_queue **ast;

    //lex = parse_lexer("echo 'hello \" world' ; ls -la rep | grep \"repertoire 1\" && sed -a -b fichier2");
    lex = parse_lexer("echo 'hello \" world' ; ls -la rep ; grep \"repertoire 1\" && sed -a -b fichier2");

    if (!lex)
    {
        print_error_lexer();
        return (1);
    }
    if (!(ast = (t_queue **)ft_memalloc(sizeof(t_queue *) * get_nbr_cmd(lex) + 1)))
    {
        print_error_ast();
        return (1);
    }
    if (!(ast = parse_ast(ast, lex)))
        print_error_ast();
    print_ast(ast);
    free_queue(lex);
    free_ast(ast);
    return (0);
}
