/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:07:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 21:06:40 by passef           ###   ########.fr       */
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
