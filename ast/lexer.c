#include "lexer.h"

t_queue     *parse_lexer(char *str)
{
    t_queue *lex;
    char    *word;
    char    *term;
    t_queue *node;

    lex = NULL;
    word = NULL;
    term = NULL;
    while (str && *str)
    {
        if (*str == '\'' || *str == '"')
         {
             str += parse_quote(&word, str);
             continue ;
         }
        if (*str && (*str == '|' || *str == '&' || *str == ';') && (term = contain_term(str)))
        {
            node = queue_new(remove_start_space(word), CMD);
            if (node && !(lex = queue_enqueue(lex, node)))
                return (NULL);
            ft_strdel(&word);
            word = NULL;
            if (!(lex = queue_enqueue(lex, queue_new(term, get_type(term)))))
                return (NULL);
            str += ft_strlen(term);
            ft_strdel(&term);
            term = NULL;
            continue ;
        }
        word = ft_str_append(word, *str++);
    }
    if (ft_strlen(word))
    {
        node = queue_new(remove_start_space(word), CMD);
        if (node && !(lex = queue_enqueue(lex, node)))
            return (NULL);
        ft_strdel(&word);
        word = NULL;
    }
    return (validate_lexer(lex));
}

int     parse_quote(char **word, char *str)
{
    int i;

    i = 1;
    if (*str == '\'' && str++)
    {
        if (str && *str && *str == '\'' && ++i)
            return (i);
        *word = ft_str_append(*word, '\'');
        while (str && *str && ++i && *str != '\'')
            *word = ft_str_append(*word, *str++);
        if (str && *str == '\'' && ++i)
            *word = ft_str_append(*word, '\'');
    }
    else if (*str == '"' && str++)
    {
        if (str && *str && *str == '"' && ++i)
            return (i);
        *word = ft_str_append(*word, '"');
        while (str && str[0] && str[0] == '"' && str[-1] != '\\' && ++i)
            *word = ft_str_append(*word, *str++);
        if (str && *str == '"' && ++i)
            *word = ft_str_append(*word, '"');
    }
    return (i);
}

t_queue     *parse_ast(t_queue *lex)
{
    t_queue *ast;
    t_queue *parent;
    t_queue *right;
    t_queue *current;

    ast = NULL;
    int i = 0;
  //  print_queue(lex);
 //   printf("**************\n\n");
    while (lex)
    {
     //   printf("\t\t\t[%s]\n", lex->name);
        current = queue_new(lex->name, lex->type);
        lex = lex->next;
        parent = lex ? queue_new(lex->name, lex->type) : queue_new("ROOT", ROOT);
        if ((!current || current->type != CMD) || !parent || (parent->type == CMD))
            return (NULL);
        lex = lex ? lex->next : lex;

        current->parent = parent;
        current->next = ast;
      //  printf("CUR +++++++++[\n");
 //       print_queue(current);
    //    printf("CUR +++++++++]\n");

        parent->next = current;
   //     printf("PAR +++++++++[\n");
     //   print_queue(parent);
  //      printf("PAR +++++++++]\n");
        if (parent->type == OP_AND || parent->type == OP_OR)
        {
            if (!lex || lex->type != CMD)
            {
                printf("NULL 2 \n");
                return (NULL);
            }
            right = queue_new(lex->name, lex->type);
            right->parent = parent;
            parent->right = right;
            lex = lex->next;
        }
        ast = parent;
    //    printf("AST +++++++++[\n");
     //   print_queue(ast);
    //    printf("AST +++++++++]\n");

    }
    printf("\nlen %d\n",queue_len(parent));
    print_queue(parent);
    return (validate_ast(ast));
}