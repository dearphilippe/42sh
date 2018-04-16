/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 23:50:39 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/16 01:33:00 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#define _POSIX_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

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

// void	builtin_fg(t_exec *cmd, t_shell *sh)
// {
//
// }

// void	builtin_ampersand()
// {
//
// }
void	builtin_jobs(t_io *fd, t_process *sh)
{
	int			i;
	char		*tmp;
	t_queue		*node;
	t_process	*pipeline;

	i = -1;
	node = init_queue();
	if (sh->p != NULL)
	{
		while (pipeline = sh->p[++i] != NULL)
		{
			//Maybe use queue or printf here?
			tmp = ft_base64encode("0123456789", (i + 1));
			ft_putstr_fd("[", fd->stdout);
			ft_putstr_fd(tmp, fd->stdout);
			ft_putstr_fd("]", fd->stdout);
			ft_putstr_fd(pipeline->fullpath, fd->stdout);
			ft_putstr_fd("\n", fd->stdout);
			free(tmp);
		}
	}
}

int main(void)
{
	pid_t pid;
	int p1[2], p2[2];
	char c = '?';

	if (pipe(p1) != 0)
		perror("pipe() #1 error");
	else if (pipe(p2) != 0)
		perror("pipe() #2 error");
	else
	{
		if ((pid = fork()) == 0)
		{
			printf("child's process group id is %d\n", (int)getpgrp());
			write(p2[1], &c, 1);
			puts("child is waiting for parent to complete task");
			read(p1[0], &c, 1);
			printf("child's process group id is now %d\n", (int)getpgrp());
			exit(0);
		}
		else
		{
			printf("parent's process group id is %d\n", (int)getpgrp());
			read(p2[0], &c, 1);
			printf("parent is performing setpgid() on pid %d\n",(int)pid);
			if (setpgid(pid, 0) != 0)
				perror("setpgid() error");
			write(p1[1], &c, 1);
			printf("parent's process group id is now %d\n", (int)getpgrp());
			sleep(5);
		}
	}
}
