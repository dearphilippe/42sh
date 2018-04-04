#include "main.h"

int     main(int argc, char **argv)
{
    t_queue *lex;

    lex = get_lexer("ls -la /doc");
    ft_printf("Len %d\n", queue_len(lex));
    return (0);
}
