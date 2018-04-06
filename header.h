#ifndef HEADER_H
# define HEADER_H

# define IS_RED_NEXT(x) (!ft_strcmp_withspace(x, ">"))
# define IS_RED_NNEXT(x) (!ft_strcmp_withspace(x, ">>"))
# define IS_RED_PREV(x) (!ft_strcmp_withspace(x, "<"))
# define IS_RED_PIPE(x) (!ft_strcmp_withspace(x, "|"))
# define IS_RED(x) (IS_RED_NEXT(x) || IS_RED_NNEXT(x) || IS_RED_PREV(x) || IS_RED_PIPE(x))

# define IS_OP_AND(x) (!ft_strcmp_withspace(x, "&&"))
# define IS_OP_OR(x) (!ft_strcmp_withspace(x, "||"))
# define IS_OP(x) (IS_OP_AND(x) || IS_OP_OR(x))

# define IS_SEP(x) (!ft_strcmp_withspace(x, ";"))

# define IS_TERM(x) (IS_OP(x)|| || IS_SEP(x) || IS_RED_PIPE(x))

# include "libft/libft.h"
# include "ft_printf/ft_printf_header.h"
# include "ft_ls/ft_ls.h"

typedef enum    e_type
{
                CMD,

                RED_NEXT,
                RED_NNEXT,
                RED_PREV,

                RED_PIPE,
                OP_AND,
                OP_OR,
                SEP
}               t_type;

// TODO to delete
# include <stdio.h>

#endif
