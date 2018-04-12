/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_me.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 13:51:43 by passef            #+#    #+#             */
/*   Updated: 2018/04/11 11:11:19 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void	error_handling(int child_pid)
{
	int status;

	if (wait(&status) == -1)
	{
		perror("Anormal exit");
	}
}

int		launch_process(pid_t	pid)
{
	pid = fork();

	while ((pid == -1) && (pid == EAGAIN))
		pid = fork();

	return (EXIT_SUCCESS);
}

int main(void)
{
	pid_t	pid;

	pid = fork();

	if (pid == 0)
	{
		printf("fils");
	}
	printf("%d", (int)pid);

	return (0);
}