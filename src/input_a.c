/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_a.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:47:31 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 15:57:01 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

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

int		backslash_prompt(t_shell *sh)
{
	if ((sh->input_size > 0) && (sh->buffer[sh->input_size - 1] == '\\'))
	{
		if ((sh->input_size > 1) && (sh->buffer[sh->input_size - 2] != '\\'))
		{
			ft_putstr("\n");
			sh->buffer[sh->input_size - 1] = '\n';
			sh->buf_i = sh->input_size;
			sh->prompt = INHIBITOR_PROMPT;
			reprint_input(sh);
			return (1);
		}
	}
	return (0);
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
			{
				if (backslash_prompt(sh))
					continue ;
				else
					return (end_of_input(sh));
			}
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
