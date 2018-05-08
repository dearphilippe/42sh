/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 15:56:16 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 15:56:59 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

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
	sh->prompt = SHELL_PROMPT;
	display_shell_prompt(sh);
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
