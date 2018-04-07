#include "parse.h"

int     main(int argc, char **argv)
{
    t_ast *lex;
    t_ast **ast;

    //lex = parse_lexer("echo 'hello \" world' ; ls -la rep | grep \"repertoire 1\" && sed -a -b fichier2");
    lex = parse_lexer("echo 'hello \" world' ; ls -la rep ; grep \"repertoire 1\" && sed -a -b fichier2");

    if (!lex)
    {
        print_error_lexer();
        return (1);
    }
    if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *) * get_nbr_instructions(lex) + 1)))
    {
        print_error_ast();
        return (1);
    }
    if (!(ast = parse_ast(ast, lex)))
        print_error_ast();
    print_trees(ast);
    free_ast(lex);
    free_trees(ast);
    return (0);
}
