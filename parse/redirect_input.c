/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytuz <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 11:35:37 by ytuz              #+#    #+#             */
/*   Updated: 2018/04/15 14:59:14 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	tsh_redirect_input(t_tsh_run *run_numbers)
{
	int		fd;

	run_numbers->stream_end = tsh_skip_spaces(run_numbers->stream_end);
	if (*(run_numbers->stream_end) != '<' &&
			ft_strnequ(run_numbers->stream_end, "0>", 2) == 0)
		return (FAILURE);
	if (*(run_numbers->stream_end) == '0')
		run_numbers->stream_end++;
	run_numbers->stream_end++;
	run_numbers->stream_end = tsh_skip_spaces(run_numbers->stream_end);
	fd = tsh_get_fd(run_numbers->stream_end, 0);
	if (fd == -1)
		ft_error("42sh: input redirection failed.\n");
	else
		dup2(0, fd);
	run_numbers->stream_end = tsh_get_next_word(run_numbers->stream_end);
	return (SUCCESS);
}
