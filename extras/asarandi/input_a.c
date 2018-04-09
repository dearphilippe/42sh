/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:47:31 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/08 03:34:02 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_input_buffer(t_shell *sh)
{
	sh->buffer = ft_memalloc(PAGE_SIZE);
	sh->bufsize = PAGE_SIZE;
	sh->buf_i = 0;
	sh->input_size = 0;
	sh->history = history_array(sh);
	sh->history_count = 0;
	if (sh->history != NULL)
		sh->history_count = count_char_array(sh->history);
	sh->history_i = 0;
	sh->partial_input = NULL;
	display_shell_prompt();
}

void	increase_buffer(t_shell *sh)
{
	char	*newbuf;

	if ((newbuf = ft_memalloc(sh->bufsize + PAGE_SIZE)) == NULL)
		fatal_error_message(sh, E_NOMEM);
	ft_strncpy(newbuf, sh->buffer, sh->bufsize);
	free(sh->buffer);
	sh->buffer = newbuf;
	sh->bufsize += PAGE_SIZE;
	return ;
}

void	raw_read(t_shell *sh)
{
	init_input_buffer(sh);
	while (1)
	{
		if (read(STDIN_FILENO, &sh->keycode, 9) < 0)
			break ;
		if (ft_isprint(sh->keycode[0]))
			insert_key_into_buffer(sh);
		else if (sh->keycode[0] == '\n')
			return (end_of_input(sh));
		else
			check_special_keys(sh);
		if (sh->input_size >= sh->bufsize)
			(void)increase_buffer(sh);
	}
	return ;
}

void	clear_input_buffers(t_shell *sh)
{
	if (sh->partial_input != NULL)
		free(sh->partial_input);
	if (sh->history != NULL)
		destroy_char_array(sh->history);
	sh->history = NULL;
	destroy_char_array(sh->child_argv);
	sh->child_argv = NULL;
	free(sh->buffer);
	sh->buffer = NULL;
	return ;
}
