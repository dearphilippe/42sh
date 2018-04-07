/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:06:58 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/06 07:34:32 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cmd_index(char *cmd)
{
	int			i;
	const char	*builtin_list[] = {
		"echo", "cd", "setenv", "unsetenv", "env", "exit", "help"};

	i = 0;
	while (i < NUM_BUILTINS)
	{
		if (ft_strcmp(cmd, builtin_list[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	builtin_echo(t_shell *sh)
{
	int	dash_n;
	int	i;

	dash_n = 0;
	if (sh->child_argv[1] != NULL)
	{
		if (ft_strcmp(sh->child_argv[1], "-n") == 0)
			dash_n = 1;
		i = 1 + dash_n;
		while (sh->child_argv[i] != NULL)
		{
			ft_printf(STDOUT_FILENO, "%s", sh->child_argv[i]);
			if (sh->child_argv[++i] != NULL)
				ft_printf(STDOUT_FILENO, " ");
		}
	}
	if (dash_n == 0)
		ft_printf(STDOUT_FILENO, "\n");
}

void	builtin_cd(t_shell *sh)
{
	char	*cwd;
	char	*path;

	if ((sh->child_argv[1] != NULL) && (sh->child_argv[2] != NULL))
		return ((void)ft_printf(STDERR_FILENO, E_TOOMANY2, "cd"));
	if ((sh->child_argv[1] == NULL) || (ft_strcmp(sh->child_argv[1], "~") == 0))
	{
		if ((path = kv_array_get_key_value(sh->envp, "HOME")) == NULL)
			return ((void)ft_printf(STDERR_FILENO, E_NOVARIABLE, "$HOME"));
	}
	else if ((ft_strcmp(sh->child_argv[1], "-")) == 0)
	{
		if ((path = kv_array_get_key_value(sh->envp, "OLDPWD")) == NULL)
			return ((void)ft_printf(STDERR_FILENO, E_NOVARIABLE, "$OLDPWD"));
	}
	else
		path = sh->child_argv[1];
	cwd = NULL;
	cwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		if (cwd != NULL)
			free(cwd);
		return ((void)ft_printf(STDERR_FILENO, E_CHDIRFAIL));
	}
	if (cwd != NULL)
	{
		kv_array_set_key_value(&sh->envp, "OLDPWD", cwd);
		free(cwd);
	}
	if ((cwd = getcwd(NULL, 0)) == NULL)
		ft_printf(STDERR_FILENO, "%s\n", E_CWDFAIL);
	else
	{
		kv_array_set_key_value(&sh->envp, "PWD", cwd);
		free(cwd);
	}
}

void	builtin_exit(t_shell *sh)
{
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	if (sh->child_argv[1] != NULL)
		exit_code = ft_atoi(sh->child_argv[1]);
	ft_printf(STDERR_FILENO, "exit\n");
	clean_up(sh);
	exit(exit_code);
	return ;
}

void	builtin_help(t_shell *sh)
{
	sh->bufsize += 0;
	return ;
}
