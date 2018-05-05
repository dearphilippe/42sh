/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:47:31 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/05 13:41:10 by asarandi         ###   ########.fr       */
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

void	close_quotes(t_shell *sh)
{
	sh->buffer[sh->input_size++] = '\n';
	sh->buf_i = sh->input_size;
	ft_putstr("\n");
	reprint_input(sh);
	while (1)
	{
		if (read(STDIN_FILENO, &sh->keycode, 9) < 0)
			break ;
		if (ft_isprint(sh->keycode[0]))
			insert_key_into_buffer(sh);
		else if (sh->keycode[0] == '\n')
		{
			if (has_paire_quote(sh))
				return (end_of_input(sh));
			return (close_quotes(sh));
		}
		else
			check_special_keys(sh);
		if (sh->input_size >= sh->bufsize)
			(void)increase_buffer(sh);
	}
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
		{
			if (has_paire_quote(sh))
				return (end_of_input(sh));
			sh->prompt = SHELL_QUOTE_PROMPT;
			return (close_quotes(sh));
		}
		else
			check_special_keys(sh);
		if (sh->input_size >= sh->bufsize)
			(void)increase_buffer(sh);
	}
	return ;
}

int		has_paire_quote(t_shell *sh)
{
	int		quotes;
	char	*str;

	str = sh->buffer;
	quotes = 0;
	if (str && *str)
	{
		if (*str == '\'' && *str == '"')
			++quotes;
		str++;
	}
	while (str && *str)
	{
		if ((str[0] == '\'' || str[0] == '"') && str[-1] != '\\')
			quotes++;
		str++;
	}
	return (quotes % 2 ? 0 : 1);
}
