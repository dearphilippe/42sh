#include "parse.h"

int     main(void)
{
    t_ast *lex;
    t_ast **ast;

     lex = parse_lexer("echo \"$HOME\"asd && cd $PWD || cat ");
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
