#include "lexer.h"

t_queue     *get_lexer(char *str)
{
    t_queue *lex;
    char    *word;
    char    *term;

    lex = NULL;
    word = NULL;
    term = NULL;
    while (str && *str)
    {
        if (*str == '\'' || *str == '"')
         {
             str += handle_quote(&word, str);
             continue ;
         }
        if (*str && (*str == '|' || *str == '&' || *str == ';') && (term = contain_term(str)))
        {
            if (!(lex = queue_enqueue(lex, queue_new(word, CMD))))
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
        if (!(lex = queue_enqueue(lex, queue_new(word, CMD))))
            return (NULL);
        ft_strdel(&word);
        word = NULL;
    }
    return (validate_lexer(lex));
}

int     handle_quote(char **word, char *str)
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
