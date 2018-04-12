/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 20:54:37 by passef            #+#    #+#             */
/*   Updated: 2018/04/11 14:17:14 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

/*
pid_t fork(void);
pid_t getpid(void); // pid du process appelant
pid_t getppid(void); // ppid du process appelant
*/
pid_t	launch_process(void)
{
	pid_t	pid;

	while (pid == -1 || pid == EAGAIN)
		pid = fork();

	return (pid);
}

void	child_process(void)
{
	printf("process fils.\n" "PID fils :%d\n" "PID père : %d\n", getpid(), getppid());
}

void	father_process(int child_pid)
{
	printf("process père.\n" "PID fils :%d\n" "PID père : %d\n", child_pid, getpid());
}

int		main(void)
{
	pid_t pid;
	pid = launch_process();

	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else if (pid == 0)
		child_process();
	else
		father_process(pid);

	if (wait(NULL) == -1)
		perror("wait :");

	return (EXIT_SUCCESS);
}