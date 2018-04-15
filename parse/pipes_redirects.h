/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirects.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytuz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:35:46 by ytuz              #+#    #+#             */
/*   Updated: 2018/04/13 15:35:49 by ytuz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

iypedef struct	s_run
{
	int			pipe[2];
	int			last_process_status;
	char		is_pipe;
	char		*command_head;
	char		*command_end;
	char		*stream_end;
	char		*line_head;
	t_main		*main_struct;
	pid_t		pid;
}				t_run;

/*
 * main_struct =
 * the general struct that contains relevant information
 */

/*
 * run_numbers is the name of the typedef t_run
 * as in
 * t_run	*run_numbers;
 */

int					parse_pipe(t_main *main_numbers, char *start_of_pipe);

/* SUCCESS or FAILRUE are returned
 * main_numbers refers to the main struct that holds information in the project
 * start_of_pipe refers to the first byte of the pipe
 */

int					run_command(t_run *run_numbers); /* status is returned */

unsigned int		count_word_length(char *word);

/* count bytes until ' ' or ';' or 0 */

char				*skip_spaces(char *address);

/* skip spaces */

char				*get_next_word(char *address);

/* skip non-spaces first. then skip spaces */

char				*skip_beginning(char *address);

/* skip ' ' and '\t'
 * '\t' is skipped if it's in the beginning of the input
 */

int					redirect_output(t_run *run_numbers);

/*
 * uses open, dup2, close
 * returns SUCCESS on valid syntax
 * also returns SUCCESS if syntax is valid but file is invalid
 * invalid file returns -1 upon open
 * will print "42sh: output redirection failed\n" on invalid fd
 * returns FAILURE on invalid syntax such as "5>" "9<<"
 */

int					redirect_input(t_run *run_numbers);

/*
 * similar to the function above
 */

int					get_fd(char *file_head, int is_append);

/*
 * returns fd (-1 on file failure)
 * if (is_append == TRUE) open will add O_APPEND
 * the path for open start as file_head
 * the path for open ends at the first ' ' or ';' or 0
 */
