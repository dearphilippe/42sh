/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 07:11:01 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/11 12:39:44 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_setenv_kv(t_shell *sh, int arg_count)
{
	char	*key;
	char	*value;

	key = sh->child_argv[1];
	value = EMPTY_STRING;
	if (arg_count == 3)
		value = sh->child_argv[2];
	if (is_alphanumeric_string(key) == 1)
	{
		if (ft_isalpha(key[0]))
		{
			kv_array_set_key_value(&sh->envp, key, value);
			return (0);	//success
		}
		else
			ft_printf(STDERR_FILENO, "setenv: %s\n", E_LETTER);
	}
	else
		ft_printf(STDERR_FILENO, "setenv: %s\n", E_ALNUM);
	return (1); //failure
}

int		builtin_setenv(t_shell *sh)
{
	int		count;

	count = count_char_array(sh->child_argv);
	if (count == 1)
		return (builtin_env(sh));
	else if (count == 2)
		return (builtin_setenv_kv(sh, 2));
	else if (count == 3)
		return (builtin_setenv_kv(sh, 3));
	else if (count > 3)
		ft_printf(STDERR_FILENO, "setenv: %s\n", E_TOOMANY);
	return (0);	//success
}

int		builtin_unsetenv(t_shell *sh)
{
	char	*key;
	int		i;
	int		count;

	count = count_char_array(sh->child_argv);
	i = 1;
	while (i < count)
	{
		key = sh->child_argv[i];
		kv_array_remove_key(sh->envp, key);
		i++;
	}
	if (i == 1)
	{
		ft_printf(STDERR_FILENO, "unsetenv: %s\n", E_TOOFEW);
		return (1);	//failure
	}
	return (0);	//success
}

int		builtin_env(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->envp[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", sh->envp[i]);
		i++;
	}
	return (0);	//success
}
