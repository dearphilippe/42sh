/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 21:09:07 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 21:19:04 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int		*group_process_make_pipes(t_process **group, int *i, int *count)
{
	int	*pipes;

	*i = 0;
	while (group[*i] != NULL)
		(*i)++;
	*count = *i;
	pipes = ft_memalloc((*count) * 2 * sizeof(int));
	*i = 0;
	while (*i < *count - 1)
	{
		pipe(pipes + ((*i) * 2));
		(*i)++;
	}
	(*i) = 0;
	return (pipes);
}

int		group_process_close_pipes(int *pipes, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(pipes[i * 2]);
		close(pipes[(i * 2) + 1]);
		i++;
	}
	free(pipes);
	return (0);
}
