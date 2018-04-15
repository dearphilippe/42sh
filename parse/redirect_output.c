/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytuz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 11:55:42 by ytuz              #+#    #+#             */
/*   Updated: 2018/04/13 12:26:31 by ytuz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	tsh_check_output_redirect(char *redirect_head)
{
	if (*redirect_head != '>' && ft_strnequ(redirect_head, "0>", 2) == 0
			&& ft_strnequ(redirect_head, "1>", 2) == 0)
		return (FAILURE);
	return (SUCCESS);
}

int	tsh_redirect_output(t_tsh_run *run_numbers)
{
	int		fd;
	int		is_append;
	int		fd_to_dup;

	is_append = 0;
	run_numbers->stream_end = tsh_skip_spaces(run_numbers->stream_end);
	if (tsh_check_output_redirect(run_numbers->stream_end) == FAILURE)
		return (FAILURE);
	fd_to_dup = 1;
	if (*(run_numbers->stream_end) == '2')
		fd_to_dup = 2;
	if (*(run_numbers->stream_end) != '>')
		run_numbers->stream_end++;
	run_numbers->stream_end++;
	if (*(run_numbers->stream_end == '>'))
	{
		is_append = 1;
		run_numbers->stream_end++;
	}
	run_numbers->stream_end = tsh_skip_spaces(run_numbers->stream_end);
	fd = tsh_get_fd(run_numbers->stream_end, is_append);
	if (fd == -1)
		ft_error("42sh: output redirection failed.\n");
	else
		dup2(fd_to_dup, fd);
	run_numbers->stream_end = tsh_get_next_word(run_numbers->stream_end);
	return (SUCCESS);
}
