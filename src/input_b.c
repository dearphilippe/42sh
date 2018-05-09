/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 07:05:45 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/08 18:41:43 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

void	display_shell_prompt(t_shell *sh)
{
	ft_printf(STDOUT_FILENO, "{green}%s{eoc}", sh->prompt);
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

void	reprint_input(t_shell *sh)
{
	int	move_left;

	ft_putstr(sh->carriage_return);
	ft_putstr(sh->clear_down);
	display_shell_prompt(sh);
	move_left = ft_strlen(sh->buffer) - 1;
	while ((move_left >= 0) && (sh->buffer[move_left] != '\n'))
		move_left--;
	move_left++;
	ft_printf(STDOUT_FILENO, &sh->buffer[move_left]);
	move_left = ft_strlen(sh->buffer) - sh->buf_i;
	while (move_left--)
		ft_putstr(sh->cursor_move_left);
	return ;
}

void	insert_key_into_buffer(t_shell *sh)
{
	size_t	size;

	if (sh->buffer[sh->buf_i] != 0)
	{
		size = sh->input_size;
		while (size > sh->buf_i)
		{
			sh->buffer[size] = sh->buffer[size - 1];
			size--;
		}
	}
	size = 0;
	while (ft_isprint(sh->keycode[size]))
	{
		sh->buffer[sh->buf_i++] = sh->keycode[size];
		sh->keycode[size++] = 0;
		sh->input_size++;
	}
	reprint_input(sh);
	return ;
}

void	end_of_input(t_shell *sh)
{
	if (ft_strlen(sh->buffer) > 0)
		(void)history_append_to_file(sh);
	(void)ft_printf(STDOUT_FILENO, "\n");
	return ;
}
