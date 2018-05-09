/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_keys_a_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 00:36:38 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/09 00:36:39 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

void	key_left_arrow_function(t_shell *sh)
{
	if (sh->buf_i > 0)
	{
		if (sh->buffer[sh->buf_i - 1] != '\n')
		{
			sh->buf_i--;
			ft_putstr(sh->cursor_move_left);
		}
	}
	return ;
}

void	key_right_arrow_function(t_shell *sh)
{
	if (sh->buf_i < sh->input_size)
	{
		sh->buf_i++;
		ft_putstr(sh->cursor_move_right);
	}
	return ;
}

void	key_backspace_function(t_shell *sh)
{
	size_t	tempo;

	if (sh->buf_i > 0)
	{
		if (sh->buffer[sh->buf_i - 1] != '\n')
		{
			key_left_arrow_function(sh);
			tempo = sh->buf_i;
			while ((tempo < sh->input_size) && sh->buffer[sh->buf_i != '\n'])
			{
				sh->buffer[tempo] = sh->buffer[tempo + 1];
				tempo++;
			}
			sh->buffer[tempo] = 0;
			sh->input_size--;
			reprint_input(sh);
		}
	}
	return ;
}

void	key_delete_function(t_shell *sh)
{
	size_t	tempo;

	if (sh->input_size > sh->buf_i)
	{
		tempo = sh->buf_i;
		while (tempo < sh->input_size)
		{
			sh->buffer[tempo] = sh->buffer[tempo + 1];
			tempo++;
		}
		sh->buffer[tempo] = 0;
		sh->input_size--;
		reprint_input(sh);
	}
	return ;
}
