/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztisnes <ztisnes@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 18:25:40 by ztisnes           #+#    #+#             */
/*   Updated: 2018/04/15 18:33:47 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
int main() {

	Queue* q = init_queue();

	printf("Empty? %d\n", isEmpty(q));
	printf("Enqueueing 'Hello'\n");
	ft_enqueue(q, "Hello");
	printf("Empty? %d\n", isEmpty(q));
	printf("Peeking: %s\n", peek_queue(q));
	printf("Enqueueing 'World'\n");
	ft_enqueue(q, "World");
	printf("Empty? %d\n", isEmpty(q));
	printf("Peeking: %s\n", peek_queue(q));
	printf("Enqueueing ':)'\n");
	ft_enqueue(q, ":)");
	printf("Empty? %d\n", isEmpty(q));
	printf("Peeking: %s\n", peek_queue(q));
	printf("Dequeue: %s\n", ft_dequeue(q));
	printf("Dequeue: %s\n", ft_dequeue(q));
	printf("Dequeue: %s\n", ft_dequeue(q));
	printf("Dequeue: %s\n", ft_dequeue(q));
	printf("Empty? %d\n", isEmpty(q));

	return 0;
}
