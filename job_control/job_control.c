/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 23:50:39 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 15:57:58 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** //TODO:
** jobs: Display the current program that is executed from the list
** job control functions that returns true or/and false when program is successful
** Create a signal with the PID once it is suspended after command is running (bg, fg)
** Ctrl Z for suspend -> kill(pid, SIGSTOP)
** Ctrl C kills the process -> kill(pid, SIGINT)
** fg: foreground
** bg: background
** &: echos the process
*/

void	builtin_bg(t_exec *cmd, t_shell *sh)
{

}

void	builtin_fg(t_exec *cmd, t_shell *sh)
{

}

void	builtin_jobs(t_exec *cmd, t_shell *sh)
{
	int		i;
	char	*tmp;

	i = -1;
	/*while the process is still running (add ++i here)
		ft_printf(STDOUT_FILENO, "[");
		ft_printf(STDOUT_FILENO, number of the stack process);
		ft_printf(STDOUT_FILENO, "]");
		ft_printf(STDOUT_FILENO, the process that its running\n);
		free(tmp);
	*/
}
void	builtin_ampersand()
