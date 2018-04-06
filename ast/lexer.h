#ifndef LEXER_H
# define LEXER_H

# include "../header.h"
# include "queue.h"
# include "helper.h"
# include "get.h"
# include "validate.h"
# include "print.h"

t_queue     *get_lexer(char *str);
int     handle_quote(char **word, char *str);

#endif
