/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 21:09:07 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 04:23:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int		close_pipes(t_process **group)
{
	int i;

	i = 0;
	while (group[i + 1] != NULL)
	{
		close(group[i]->fd0);
		close(group[i]->fd1);
		i++;
	}
	return (0);
}

void	group_process_destroy(t_process **group)
{
	int	i;

	i = 0;
	while (group[i] != NULL)
	{
		(void)process_destroy(group[i]);
		i++;
	}
	free(group);
	return ;
}

int		group_process_wait(t_process **group)
{
	int i;
	int pid;
	int	status;

	pid = 0;
	status = 0;
	while ((pid = wait(&status)) != -1)
	{
		i = 0;
		while (group[i])
		{
			if (group[i]->pid == pid)
			{
				group[i]->exit_code = WEXITSTATUS(status);
				break ;
			}
			i++;
		}
	}
	return (status);
}
