/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 11:11:24 by passef            #+#    #+#             */
/*   Updated: 2018/04/02 10:52:51 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_e(t_env *e)
{
	
}

/*
** Initialize the prompt with basic loop
** Read stdin and store line
*/

char	*fts_read_line(void)
{
	int		i;
	char	*buff;
	int		buff_size;

	i = 0;
	buff_size = 255;

	if (!(buff = malloc(sizeof(buff) * buff_size)))
	{
		ft_putstr_fd("Allocation error\n", 2);
		exit(EXIT_FAILURE);
	}

	while (42)
	{
		
		// read(1, &buff, buff_size);
		// ft_putstr(&buff[i]);
		i++;
	}
}

void	fts_loop(void)
{
	char	*line;
	int		state;

	state = 1;
	while (state)
	{
		ft_putstr("42sh ~ ");
		line = fts_read_line();
		free(line);
	}
}

int main(void)
{
	fts_loop();

	return EXIT_SUCCESS;
}
