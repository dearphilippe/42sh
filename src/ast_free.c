/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/22 02:35:20 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

void	free_ast(t_ast *ast)
{
	t_ast	*next;
	t_ast	*right;

	if (!ast)
		return ;
	while (ast)
	{
		next = ast->next;
		right = ast->right;
		if (right)
		{
			ft_strdel(&right->name);
			ft_memdel((void **)&right);
		}
		ft_strdel(&ast->name);
		ft_memdel((void **)&ast);
		ast = next;
	}
}

void	free_trees(t_ast **ast)
{
	int i;

	i = 0;
	while (ast && ast[i])
	{
		free_ast(ast[i]);
		ast++;
	}
}

size_t	free_parse_ast(char **term)
{
	size_t i;

	i = ft_strlen(*term);
	ft_strdel(term);
	return (i);
}
