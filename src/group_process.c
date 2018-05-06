/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:11:18 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 04:29:17 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

void	group_fix_pipes(t_process **group, int i)
{
	int	k;

	k = 0;
	while (group[k] != NULL)
		k++;
	if ((i > 0) && (group[i]->ast->type == CMD))
		dup2(group[i - 1]->fd0, 0);
	if ((i < k - 1) && (group[i]->ast->type == CMD))
		dup2(group[i]->fd1, 1);
	return ;
}

void	group_fork_exec(t_process **group, int i)
{
	t_process	*p;
	int			x;

	p = group[i];
	(void)group_fix_redirect(group, i);
	x = -1;
	if ((p->pid = fork()) == 0)
	{
		x = group[i]->ast->parent->type;
		if (x == RED_NEXT || x == RED_NNEXT || x == RED_PREV)
			process_redirects(group, i);
		else
			group_fix_pipes(group, i);
		(void)close_pipes(group);
		execve(p->fullpath, p->argv, p->envp);
	}
	else if (p->pid == -1)
		(void)fatal_error_message(g_sh, E_FORK);
	return ;
}

int		group_process_fix_path(t_process **group, int i)
{
	char *path;

	path = NULL;
	if (is_valid_executable_file(group[i]->argv[0]) == 1)
	{
		group[i]->fullpath = ft_strdup(group[i]->argv[0]);
		return (0);
	}
	else
	{
		if ((path = find_command_path(g_sh, group[i]->argv[0])) == NULL)
		{
			free(path);
			(void)ft_printf(STDERR_FILENO, "%s: %s: command not found\n",
					SHELL_NAME, group[i]->argv[0]);
			return (close_pipes(group) + 1);
		}
		group[i]->fullpath = dir_slash_exec(path, group[i]->argv[0]);
		free(path);
	}
	return (0);
}

int		group_process_execute(t_shell *sh, t_process **group, int i)
{
	sh->buf_i += 0;
	i = 0;
	while (group[i + 1] != NULL)
	{
		pipe(&group[i]->fd0);
		i++;
	}
	i = 0;
	while (group[i])
	{
		if (group[i]->ast->type == CMD)
		{
			if (group_process_fix_path(group, i) != 0)
				return (1);
			(void)group_fork_exec(group, i);
		}
		i++;
	}
	return (close_pipes(group));
}
