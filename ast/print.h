#ifndef PRINT_H
# define PRINT_H

# include "../header.h"
# include "queue.h"

void	print_queue(t_queue *node);
void	print_ast(t_queue **ast);
void	print_lexer_start_error(char *name);
void	print_error_lexer(void);
void	print_error_ast(void);

#endif
