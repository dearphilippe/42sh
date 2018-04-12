/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 01:49:49 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/12 01:52:40 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *g_builtin_list[] = {
		"cd", "echo", "env",
		"exit", "setenv", "unsetenv"};

char *g_punani_list[] = {
		"Compact disc; access to other folders or directories",
		"Display given string", "Set environment and execute command, or print\
		environment", "Terminate program", "function inserts or resets the\
		environment variable name in the current environment list",
		"function deletes all instances of the variable name pointed to\
		by name from the list"
	};

void	help_selection(char *cmd)
{
	int i;

	i = 0;
	while (g_builtin_list[i] != '\0')
	{
		if (g_builtin_list[i] && (i >= 0))
		{
			if (ft_strcmp(cmd ,g_builtin_list[i]) == 0)
				return (void)printf("Only if I'm %s -> %s\n", \
				g_builtin_list[i], g_punani_list[i]);
			i++;
		}
	}
}

void	help_list(void)
{
	int	i;

	i = 0;
	while (g_builtin_list[i] != '\0')
	{
		if (g_builtin_list[i] && (i >= 0))
		{
			printf("Only if im %s -> ", g_builtin_list[i]);
			if (i == 0)
				printf("\taccess directories/folder\n");
			else if (i == 1)
				printf("\tprint stuff\n");
			else if (i == 2)
				printf("\tenv stuff\n");
			else if (i == 3)
				printf("\texit stuff\n");
			else if (i == 4)
				printf("\tsetenv stuff\n");
			else if (i == 5)
				printf("\tunsetenv stuff\n");
			else
				break ;
			i++;
		}
	}
}
