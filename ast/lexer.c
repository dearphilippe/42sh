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

t_queue     **parse_ast(t_queue **ast, t_queue *lex)
{
    int i;

    i = 0;
    ast[i] = NULL;
    while (lex)
    {
        if (lex->type == SEP)
            ast[++i] = NULL;
        else if (!(ast[i] = queue_enqueue(ast[i], queue_new(lex->name, lex->type))))
            return (NULL);
        lex = lex->next;
    }
    ast[++i] = 0;
    i = 0;
    while (ast[i])
    {
        if (!(ast[i] = parse_tree(ast[i])))
            return (NULL);
        i++;
    }
    return (ast);
}

t_queue     *parse_tree(t_queue *lex)
{
    t_queue *ast;
    t_queue *op;
    t_queue *right;
    t_queue *cpy;

    if (!lex || lex->type != CMD || !(ast = queue_new(lex->name, lex->type)))
        return (NULL);
    cpy = lex;
    lex = lex->next;
    while (lex)
    {
        if (lex->type == CMD || !(op = queue_new(lex->name, lex->type)))
            return (NULL);
        lex = lex->next;
        if (!lex || lex->type != CMD || !(right = queue_new(lex->name, lex->type)))
            return (NULL);
        op->next = ast;
        op->right = right;
        right->parent = op;
        ast->parent = op;
        ast = op;
        lex = lex->next;
    }
    free_queue(cpy);
    return (ast);
}
