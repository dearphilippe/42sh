/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/06 08:02:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(t_shell *sh)
{
	termios_restore_settings(sh);
	if (sh->envp != NULL)
		destroy_char_array(sh->envp);
	if (sh->history != NULL)
		destroy_char_array(sh->history);
	if (sh->child_argv != NULL)
		destroy_char_array(sh->child_argv);
	if (sh->buffer != NULL)
		free(sh->buffer);
	if (sh != NULL)
		free(sh);
}

void	fatal_error(t_shell *sh)
{
	clean_up(sh);
	exit(EXIT_FAILURE);
}

void	fatal_error_message(t_shell *sh, char *msg)
{
	ft_printf(STDERR_FILENO, "%s: error: %s\n", SHELL_NAME, msg);
	fatal_error(sh);
}

t_shell	*init_shell(int argc, char **argv, char **envp)
{
	t_shell	*sh;

	if ((sh = ft_memalloc(sizeof(t_shell))) == NULL)
		fatal_error_message(sh, E_NOMEM);
	sh->argc = argc;
	sh->argv = argv;
	sh->envp = create_char_array_copy(envp, 0);
	terminal_init(sh);
	return (sh);
}

int		main(int argc, char **argv, char **envp)
{
	t_shell		*sh;
	int			r;
	static void	(*builtin_functions[]) (t_shell *) = {&builtin_echo,
		&builtin_cd, &builtin_setenv, &builtin_unsetenv, &builtin_env,
		&builtin_exit, &builtin_help};

	sh = init_shell(argc, argv, envp);
	while (1)
	{
		raw_read(sh);
		if (sh->buffer == NULL)
			break ;
		if ((build_child_argv_list(sh, 0, 0, 1) == 1)
				&& (sh->child_argv[0] != NULL))
		{
			if ((r = builtin_cmd_index(sh->child_argv[0])) != -1)
				(void)builtin_functions[r](sh);
			else
				(void)execute_external_cmd(sh);
		}
		clear_input_buffers(sh);
	}
	clean_up(sh);
	return (0);
}
