/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:24:10 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 03:44:45 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*file_get_contents(char *filename)
{
	int			fd;
	struct stat	st;
	char		*data;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	data = NULL;
	if ((fstat(fd, &st)) == 0)
	{
		if ((data = ft_memalloc(st.st_size + 1)) == NULL)
		{
			(void)close(fd);
			return (NULL);
		}
		if ((read(fd, data, st.st_size)) != st.st_size)
		{
			free(data);
			data = NULL;
		}
	}
	(void)close(fd);
	return (data);
}
