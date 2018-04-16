/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:39:20 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/11 17:13:12 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_av	*init_av_buffers(char *cmd)
{
	t_av	*av;

	if ((av = ft_memalloc(sizeof(t_av))) == NULL)
		return (NULL);
	av->argv = ft_memalloc(sizeof(char *));
	av->argv[0] = NULL;
	av->in = cmd;
	if ((av->out = ft_memalloc(PAGE_SIZE * 2)) == NULL)
	{
		cleanup_av_buffers(av);
		return (NULL);
	}
	if ((av->key = ft_memalloc(PAGE_SIZE)) == NULL)
	{
		cleanup_av_buffers(av);
		return (NULL);
	}
	av->val = NULL;
	return (av);
}
