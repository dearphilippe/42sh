/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 06:00:59 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/11 13:02:13 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		fork_exec_wait(t_shell *sh, char *fullpath)
{
	pid_t	child;
	int		status;
	int		exit_code;

	exit_code = 0;
	if ((child = fork()) == -1)
		fatal_error_message(sh, E_FORK);
	else if (child == 0)
		execve(fullpath, sh->child_argv, sh->envp);
	if (waitpid(child, &status, 0) == -1)
	{
		(void)perror(SHELL_NAME);
		return (1);
	}
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}

int		execute_external_cmd(t_shell *sh)
{
	char	*path;
	char	*fullpath;
	int		exit_code;

	exit_code = 0;
	if (is_valid_executable_file(sh->child_argv[0]) == 1)
		return (fork_exec_wait(sh, sh->child_argv[0]));
	else
	{
		if ((path = find_command_path(sh, sh->child_argv[0])) == NULL)
		{
			(void)perror(SHELL_NAME);
			return (1);	//failure
		}
		fullpath = dir_slash_exec(path, sh->child_argv[0]);
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_original);
		exit_code = fork_exec_wait(sh, fullpath);
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_custom);
		free(path);
		free(fullpath);
	}
	return (exit_code);
}
