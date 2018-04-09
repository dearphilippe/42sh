#ifndef PARSE_H
# define PARSE_H

# define IS_RED_NEXT(x) (!ft_strcmp_withspace(x, ">"))
# define IS_RED_NNEXT(x) (!ft_strcmp_withspace(x, ">>"))
# define IS_RED_PREV(x) (!ft_strcmp_withspace(x, "<"))
# define IS_RED_PIPE(x) (!ft_strcmp_withspace(x, "|"))
# define IS_RED(x) (IS_RED_NEXT(x) || IS_RED_NNEXT(x) || /
					IS_RED_PREV(x) || IS_RED_PIPE(x))

# define IS_OP_AND(x) (!ft_strcmp_withspace(x, "&&"))
# define IS_OP_OR(x) (!ft_strcmp_withspace(x, "||"))
# define IS_OP(x) (IS_OP_AND(x) || IS_OP_OR(x))

# define IS_SEP(x) (!ft_strcmp_withspace(x, ";"))

# define IS_TERM(x) (IS_OP(x) || IS_SEP(x) || IS_RED_PIPE(x))

# include "../libft/libft.h"
# include "../ft_printf/ft_printf_header.h"
# include "../ft_ls/ft_ls.h"

/* TODO to delete this shit before is too late*/
# include <stdio.h>
/* TODO to delete this shit before is too late*/

typedef enum		e_type
{
					CMD,

					RED_NEXT,
					RED_NNEXT,
					RED_PREV,

					RED_PIPE,
					OP_AND,
					OP_OR,
					SEP,
					ROOT
}					t_type;

typedef struct		s_ast
{
	char			*name;
	struct s_ast	*parent;
	struct s_ast	*next;
	struct s_ast	*right;
	t_type			type;
}					t_ast;


/*
**	free.c
*/
void				free_ast(t_ast *head);
void				free_trees(t_ast **ast);

/*
**	get.c
*/
t_type				get_type(char *str);
int					get_nbr_instructions(t_ast *lex);

/*
**	helper.c
*/
char				*contain_term(char *str);
char				*remove_start_space(char *str);

/*
**	lexer.c
*/
 t_ast				**parse_ast(t_ast **ast, t_ast *lex);
t_ast				*parse_lexer(char *str);
t_ast				*parse_tree(t_ast *lex);
int					parse_quote(char **word, char *str);

/**
 * print.c
 */
void				print_ast(t_ast *node);
void				print_trees(t_ast **ast);
void				print_lexer_start_error(char *name);
void				print_error_lexer(void);
void				print_error_ast(void);

/**
 * ast.c
 */
t_ast				*ast_new(char *name, t_type type);
t_ast				*ast_enast(t_ast *head, t_ast *node);
t_ast				*ast_deast(t_ast *head);
t_ast				*ast_deast_front(t_ast *head);
int					ast_len(t_ast *head);

/*
**	validate.c
*/
t_ast				*validate_lexer(t_ast *lex);
t_ast				*validate_ast(t_ast *ast);

#endif
