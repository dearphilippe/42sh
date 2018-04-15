/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 15:14:51 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	free_ast(t_ast *head)
{
	head->name = NULL;
}

void	free_trees(t_ast **ast)
{
	while (ast && *ast)
	{
		free_ast(*ast);
		ast++;
	}
}
