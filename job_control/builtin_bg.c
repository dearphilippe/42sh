/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 01:27:04 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/16 03:00:51 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell"
#include <stdio.h>

// int		getnum(char *str)
// {
// 	int	num;
// 	int	sign;
//
// 	num = 0;
// 	if (str == NULL)
// 		return (num);
// 	str = getsign()
// }

int		ft_atoi(char *str)
{
	int		i;
	int		flag;
	long	number;

	i = 0;
	flag = 1;
	number = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') \
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '-')
		flag = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		number *= 10;
		number += ((int)str[i] - '0');
		i++;
	}
	return (number * flag);
}

void	builtin_bg(t_process *cmd, t_group *sh)
{
	int	num;
	int	i;
	int	pgid;

	i = 0;
	num = 0;
	if (!sh->p)
		return ;
	if (cmd->argv[1])
		num = ft_atoi((cmd->argv[1]) - 1);
	while ((sh->p[i] != NULL) && (i < num))
		i++;
	if (sh->p[i] != NULL)
		{
			pgid = sh->p[i]->pid.pgid;
			printf("%d\n", pgid);
			kill(-pgid, SIGCONT);
		}
}
