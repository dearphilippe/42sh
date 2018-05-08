/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_localvar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 07:11:01 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 15:39:51 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

/*
** builtin_export
** builtin_unexport
** builtin_printlocal
** sh->localvar
*/

int		builtin_export_kv(t_shell *sh, char **argv, int arg_count)
{
	char	*key;
	char	*value;

	key = argv[1];
	value = EMPTY_STRING;
	if (arg_count == 3)
		value = argv[2];
	if (is_alphanumeric_string(key) == 1)
	{
		if (ft_isalpha(key[0]))
		{
			kv_array_set_key_value(&sh->localvar, key, value);
			return (0);
		}
		else
			ft_printf(STDERR_FILENO, "export: %s\n", E_LETTER);
	}
	else
		ft_printf(STDERR_FILENO, "export: %s\n", E_ALNUM);
	return (1);
}

int		builtin_export(t_shell *sh, char **argv)
{
	int		count;

	count = count_char_array(argv);
	if (count == 1)
		return (builtin_printlocal(sh, argv));
	else if (count == 2)
		return (builtin_export_kv(sh, argv, 2));
	else if (count == 3)
		return (builtin_export_kv(sh, argv, 3));
	else if (count > 3)
	{
		ft_printf(STDERR_FILENO, "export: %s\n", E_TOOMANY);
		return (1);
	}
	return (0);
}

int		builtin_unexport(t_shell *sh, char **argv)
{
	char	*key;
	int		i;
	int		count;

	count = count_char_array(argv);
	i = 1;
	while (i < count)
	{
		key = argv[i];
		kv_array_remove_key(sh->localvar, key);
		i++;
	}
	if (i == 1)
	{
		ft_printf(STDERR_FILENO, "unexport: %s\n", E_TOOFEW);
		return (1);
	}
	return (0);
}

int		builtin_printlocal(t_shell *sh, char **argv)
{
	int	i;

	i = 0;
	argv[1] += 0;
	while (sh->localvar[i] != NULL)
	{
		ft_printf(STDOUT_FILENO, "%s\n", sh->localvar[i]);
		i++;
	}
	return (0);
}
