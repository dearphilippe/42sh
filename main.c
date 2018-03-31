/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/03/30 22:00:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

typedef struct	s_shell
{
	int			argc;
	char		**argv;
	char		**envp;
	size_t		pagesize;
	char		*buffer;
	size_t		bufsize;
}				t_shell;

#define	shell_prompt	"42sh> "
#define	shell_name		"42sh"

t_shell	*init(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	sh = ft_memalloc(sizeof(sh));
	sh->argc = argc;
	sh->argv = argv;
	sh->envp = envp;
	sh->pagesize = getpagesize();	//allowed ?
	return (sh);
}

void	clean_up(t_shell *sh)
{
	if (sh->buffer != NULL)
		free(sh->buffer);
	if (sh != NULL)
		free(sh);
}

void	fatal_error(t_shell *sh)
{
	clean_up(sh);
	perror(shell_name);				//allowed ?
	exit(EXIT_FAILURE);
}

void	increase_buffer(t_shell *sh)
{
	char	*newbuf;

	if ((newbuf = ft_memalloc(sh->bufsize + sh->pagesize)) == NULL)
		fatal_error(sh);
	ft_strncpy(newbuf, sh->buffer, sh->bufsize);
	free(sh->buffer);
	sh->buffer = newbuf;
	sh->bufsize += sh->pagesize;
}

void	get_input(t_shell *sh)
{
	size_t	i;
	ssize_t	r;

	ft_printf("%s", shell_prompt);
	if ((sh->buffer = ft_memalloc(sh->pagesize)) == NULL)
		fatal_error(sh);
	sh->bufsize = sh->pagesize;
	i = 0;
	while (1)
	{
		if ((r = read(STDIN_FILENO, &(sh->buffer)[i], 1)) == 0)	//read returns 0 on EOF
			break ;
		if (r == -1)
			fatal_error(sh);									//read returns -1 on error

		if (((sh->buffer)[i] == '\n') || ((sh->buffer)[i] == 0))
			break ;
		i++;
		if (i >= sh->bufsize)
			increase_buffer(sh);
	}
	return ;
}

int		main(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	sh = init(argc, argv, envp);
	while (1)
	{
		get_input(sh);
		if (ft_strcmp(sh->buffer, "exit") == 0)
			break ;
//		execute(sh);
		if (sh->buffer != NULL)
			free(sh->buffer);
		sh->buffer = NULL;
	}
	clean_up(sh);
	return (0);
}
