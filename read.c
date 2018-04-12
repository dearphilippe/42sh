/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:37:20 by passef            #+#    #+#             */
/*   Updated: 2018/04/04 20:05:00 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void	enableRawMode()
{
	struct	termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int		main(void)
{
	char c;

	enableRawMode();
	while(42)
	{
		read(STDIN_FILENO, &c, 1);
		if (c == 'q')
			break;
	}

	return (0);
}