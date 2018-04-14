#include "parse.h"
#include "get_next_line.h"
#include <fcntl.h>

int     ast_main3(void)
{
    t_ast *lex;
    t_ast **ast;
    char *line;

    int fd = open("file", O_RDONLY);
    line = NULL;
    get_next_line(fd, &line);

    lex = parse_lexer(line);
			 //mkdir folder | grep *file >> echo 'doc' ; ls -la /bin > mkdir file > doc2 | touch fichier2 | folder3 >>doc ; touch file");
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
