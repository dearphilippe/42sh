/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 04:28:50 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/06 04:29:20 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

void	group_fix_redirect(t_process **group, int i)
{
	char	**filename;

	if (group[i + 1] != NULL)
	{
		filename = ft_strsplit(group[i + 1]->ast->name, ' ');
		if (group[i + 1]->ast->parent->type == RED_NEXT)
		{
			group[i]->fd1 = open(filename[0], FILE_MODE1, 0644);
			if (group[i]->fd1 == -1)
				perror(SHELL_NAME);
		}
		if (group[i + 1]->ast->parent->type == RED_NNEXT)
		{
			group[i]->fd1 = open(filename[0], FILE_MODE2, 0644);
			if (group[i]->fd1 == -1)
				perror(SHELL_NAME);
		}
		if (group[i + 1]->ast->parent->type == RED_PREV)
		{
			group[i]->fd0 = open(filename[0], O_RDONLY);
			if (group[i]->fd0 == -1)
				perror(SHELL_NAME);
		}
		destroy_char_array(filename);
	}
}

void	process_redirects(t_process **group, int i)
{
	int	ast;

	if (group[i + 1] != NULL)
	{
		ast = group[i + 1]->ast->parent->type;
		if ((ast == RED_PREV) && (group[i]->fd0 > 0))
		{
			dup2(group[i]->fd0, 0);
		}
		if (((ast == RED_NEXT) || (ast == RED_NNEXT)) && (group[i]->fd1 > 0))
		{
			dup2(group[i]->fd1, 1);
		}
	}
}
