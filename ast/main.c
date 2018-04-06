#include "main.h"

int     main(int argc, char **argv)
{
    t_queue *lex;

    lex = parse_lexer("echo 'hello \" world' ; ls -la rep | grep \"repertoire 1\" && sed -a -b fichier2");
    // lex = parse_lexer("echo \"hello world\" ; ls -la repertoire | touch file && mkdir document1 document2 && grep file ; ls a /tmp/rep");
    if (lex)

    print_queue(lex);
    return (0);
}
