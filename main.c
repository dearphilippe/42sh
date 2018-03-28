/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:11:24 by passef            #+#    #+#             */
/*   Updated: 2018/03/27 16:44:27 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Initialize the prompt with basic loop
** Read stdin and store line
*/

char	*fts_read_line(void)
{
	int		position;
	char	*buff;
	int		buff_size;

	position = 0;
	buff_size = 255;

	if (!(buff = malloc(sizeof(buff) * buff_size)))
	{
		ft_putstr_fd("Allocation error\n", 2);
		exit(EXIT_FAILURE);
	}

	while (42)
	{
		read(1, &buff, buff_size);
	}
}

void	fts_loop(void)
{
	char	*line;
	int		state;

	state = 1;
	while (state)
	{
		ft_putstr("➜  ~ ");
		line = fts_read_line();
		free(line);
	}
}

int main(void)
{
	fts_loop();

	return EXIT_SUCCESS;
}
