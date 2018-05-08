/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 17:14:52 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 15:43:52 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

char	*g_builtin_list[] = {
	"cd", "echo", "env", "exit", "setenv", "unsetenv",
	"help", "export", "unexport", "printlocal"
};

char	*g_punani_list[] = {
	"Compact disc; access to other folders or directories",
	"Display given string",
	"Set environment and execute command, or print environment",
	"Terminate program",
	"function inserts or resets the environment variable name in the " \
	"current environment list",
	"function deletes all instances of the variable name pointed to by" \
	" name from the list",
	"this help message",
	"set a local variable",
	"removes a local variable",
	"show a list of local variables"
};

void	help_selection(char *cmd)
{
	int	i;

	i = 0;
	while (g_builtin_list[i] != '\0')
	{
		if (g_builtin_list[i] && (i >= 0))
		{
			if (ft_strcmp(cmd, g_builtin_list[i]) == 0)
				return (void)ft_printf(1, "\n\033[37;1m\t%s\033[0m -> %s\n\n",
				g_builtin_list[i], g_punani_list[i]);
				i++;
		}
	}
}

void	help_list(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd_title();
	while (g_builtin_list[i] != '\0')
	{
		j++;
		if (i >= 0 && i < 10)
			ft_printf(1, "\n(%d) Only if I'm \033[37;1m%s\033[0m\n\n", \
			j, g_builtin_list[i]);
		i++;
	}
}

int		builtin_help(t_shell *sh, char **argv)
{
	sh->argc += 0;
	argv[0] += 0;
	if (argv[1] != NULL)
	{
		if (argv[2])
			ft_printf(1, "No more than 1 help command. Do `help [cmd]`\n");
		else
			help_selection(argv[1]);
	}
	else
		help_list();
	return (0);
}
