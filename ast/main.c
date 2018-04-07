#include "main.h"

int     main(int argc, char **argv)
{
    t_queue *lex;
    t_queue *ast;

    lex = parse_lexer("echo 'hello \" world' ; ls -la rep | grep \"repertoire 1\" && sed -a -b fichier2");

    if (!lex)
        print_error_lexer();
    if (!(ast = parse_ast(lex)))
        print_error_ast();
    //print_queue(lex);
    //print_queue(ast);
    free_queue(lex);
    free_queue(ast);
    return (0);
}
/*
 *
echo 'hello " world'
;
ls -la rep
|
grep "repertoire 1"
&& ;
sed -a -b fichier2

 */