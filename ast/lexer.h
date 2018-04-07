#ifndef LEXER_H
# define LEXER_H

# include "../header.h"
# include "queue.h"
# include "helper.h"
# include "get.h"
# include "validate.h"
# include "print.h"

t_queue		*parse_lexer(char *str);
int			parse_quote(char **word, char *str);
t_queue		**parse_ast(t_queue **ast, t_queue *lex);
t_queue		*parse_tree(t_queue *lex);

#endif
