/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:14:55 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 17:08:52 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_sh->state == STATE_READ)
		{
			ft_bzero(g_sh->buffer, g_sh->bufsize);
			g_sh->buf_i = 0;
			g_sh->input_size = 0;
			ft_printf(STDOUT_FILENO, "\n");
			ft_printf(STDOUT_FILENO, "%s", SHELL_PROMPT);
		}
		else if (g_sh->state == STATE_EXEC)
		{
		}
	}
}
