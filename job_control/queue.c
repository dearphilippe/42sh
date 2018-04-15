/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 17:59:27 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 01:50:21 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

t_queue				*init_queue(void)
{
	t_queue			*node;
	node = (t_queue *)malloc(sizeof(t_queue));
	node->first = NULL;
	node->last = NULL;
	return (node);
}

void				ft_enqueue(t_queue *queue, void *content, size_t c_size)
{
	t_list			*node;
	(void)c_size;
	node = (t_list *)malloc(sizeof(t_list));
	node->content = content;
	// node->content = ft_memmove(node->content, content, c_size);
	node->next = NULL;
	if (!queue->last)
	{
		queue->last = node;
		queue->first = node;
	}
	else
	{
		queue->last->next = node;
		queue->last = queue->last->next;
	}
	return ;
}

void				*ft_dequeue(t_queue *queue)
{
	t_list			*temp;

	temp = queue->first;
	if (tmp)
	{
		queue->first = temp->next;
		return (temp->content);
	}
	return (NULL);
}

void 				*peek_queue(t_queue *queue)
{
	if (queue->first == NULL)
		return (NULL);
	return (queue->first->content);
}

int					isEmpty(t_queue *queue)
{
	return (queue->first == NULL);
}
