/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:47:31 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/10 22:58:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/42.h"

void	init_input_buffer(t_shell *sh)
{
	sh->buffer = ft_memalloc(POOGE);
	sh->bufsize = POOGE;
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

	if ((newbuf = ft_memalloc(sh->bufsize + POOGE)) == NULL)
		fatal_error_message(sh, E_NOMEM);
	ft_strncpy(newbuf, sh->buffer, sh->bufsize);
	free(sh->buffer);
	sh->buffer = newbuf;
	sh->bufsize += POOGE;
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
	sh->partial_input = NULL;
	if (sh->history != NULL)
		destroy_char_array(sh->history);
	sh->history = NULL;
	if (sh->child_argv != NULL)
		destroy_char_array(sh->child_argv);
	sh->child_argv = NULL;
	if (sh->buffer != NULL)
		free(sh->buffer);
	sh->buffer = NULL;
	return ;
}
