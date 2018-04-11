/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/11 13:02:29 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(t_shell *sh)
{
	termios_restore_settings(sh);
	destroy_list_of_executables(sh);
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

void	sigint_handler(int signo)
{
	ft_printf(STDOUT_FILENO, "\n");
	if (signo == SIGINT)
	{
		if (g_sh->state == STATE_READ)
		{
			ft_bzero(g_sh->buffer, g_sh->bufsize);
			g_sh->buf_i = 0;
			g_sh->input_size = 0;
			display_shell_prompt();
		}
		else if (g_sh->state == STATE_EXEC)
		{
		}
	}
}

t_shell	*init_shell(int argc, char **argv, char **envp)
{
	t_shell	*sh;
	char	**folders;
	char	*path;

	(void)signal(SIGINT, sigint_handler);
	if ((sh = ft_memalloc(sizeof(t_shell))) == NULL)
		fatal_error_message(sh, E_NOMEM);
	sh->argc = argc;
	sh->argv = argv;
	sh->envp = create_char_array_copy(envp, 0);
	terminal_init(sh);
	g_sh = sh;
	if ((path = kv_array_get_key_value(sh->envp, "PATH")) != NULL)
	{
		if ((folders = ft_strsplit(path, ':')) == NULL)
			fatal_error_message(sh, E_NOMEM);
		else
		{
			build_list_of_executables(sh, folders);
			destroy_char_array(folders);
		}
	}
	return (sh);
}

void	execute(t_shell *sh)
{
	int			r;
	int			i;
	static int	(*builtin_functions[]) (t_shell *) = {&builtin_echo,
		&builtin_cd, &builtin_setenv, &builtin_unsetenv, &builtin_env,
		&builtin_exit, &builtin_help};

	sh->state = STATE_EXEC;
	i = 0;
	if (build_child_argv_list(sh, &i, 0, 1) == 1)
	{
		if (sh->child_argv[0] != NULL)
		{
			if ((r = builtin_cmd_index(sh->child_argv[0])) != -1)
				sh->exit_code = builtin_functions[r](sh);
			else
				sh->exit_code = execute_external_cmd(sh);
		}
		if (sh->buffer[i] == ';')
		{
			ft_strcpy(sh->buffer, &sh->buffer[i + 1]);
			execute(sh);
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_shell		*sh;
    t_ast		*lex;
    t_ast		**ast;

	sh = init_shell(argc, argv, envp);
	while (1)
	{
		sh->state = STATE_READ;
		raw_read(sh);
		if (sh->buffer == NULL)
			break ;
		
///////////////////////////////////
		if ((lex = parse_lexer(sh->buffer)) == NULL)
		{
			ft_printf(STDERR_FILENO, "lexical error!!\n");
			clear_input_buffers(sh);
			continue ;
		}
	    if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *) * get_nbr_instructions(lex) + 1)))
	    {
	        ft_printf(STDERR_FILENO, "ast memory error!!\n");
			clear_input_buffers(sh);
			continue ;
	    }

	    if (!(ast = parse_ast(ast, lex)))
		{
	        ft_printf(STDERR_FILENO, "ast syntax error!!\n");
			clear_input_buffers(sh);
			continue ;
		}
//        print_error_ast();
	    print_trees(ast);
	    free_ast(lex);
	    free_trees(ast);
///////////////////////////////////
	
		execute(sh);
		clear_input_buffers(sh);
	}
	clean_up(sh);
	return (0);
}
