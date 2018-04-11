/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 06:00:59 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/11 11:56:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_exec_wait(t_shell *sh, char *fullpath)
{
	pid_t	child;

	if ((child = fork()) == -1)
		fatal_error_message(sh, E_FORK);
	else if (child == 0)
		execve(fullpath, sh->child_argv, sh->envp);
	waitpid(child, NULL, 0);
}

void	execute_external_cmd(t_shell *sh)
{
	char	*path;
	char	*fullpath;

	if (is_valid_executable_file(sh->child_argv[0]) == 1)
		fork_exec_wait(sh, sh->child_argv[0]);
	else
	{
		if ((path = find_command_path(sh, sh->child_argv[0])) == NULL)
		{
//			return ((void)ft_printf(STDERR_FILENO,
//						E_NOTFOUND, sh->child_argv[0]));
			return (perror(SHELL_NAME));
		}
		fullpath = dir_slash_exec(path, sh->child_argv[0]);
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_original);
		fork_exec_wait(sh, fullpath);
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_custom);
		free(path);
		free(fullpath);
	}
}
