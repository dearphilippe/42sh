/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 14:51:27 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/04 01:01:23 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <backend.h>
#include <error.h>

/*
**
** TODO:execve function to run the command after parsing it
**		-> Make execve be running in the leaves of the AST
**
*/

typedef struct		s_ast
{
	void			*data;
	struct s_ast	*left;
	struct s_ast	*right;
}                t_ast;

t_ast		*create_node(int *value)
{
	t_ast *root;

	root = malloc(sizeof(t_ast));
	root->data = value;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

t_ast		*insert_left(t_ast *node, int *value)
{
	node->left = create_node(value);
	return (node->left);
}

t_ast		*insert_right(t_ast *node, int *value)
{
	node->right = create_node(value);
	return (node->right);
}