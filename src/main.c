/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 04:10:48 by ztisnes          ###   ########.fr       */
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

void		sigint_handler(int signo)
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

t_shell		*init_shell(int argc, char **argv, char **envp)
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

void		process_destroy(t_process *p)
{
	if (p->argv != NULL)
		destroy_char_array(p->argv);
	free(p);
	return ;
}

t_process	*process_prepare(t_shell *sh, char *cmd)
{
	t_process	*p;

	p = ft_memalloc(sizeof(t_process));
	p->argv = build_child_argv_list(sh, cmd);
	if (p->argv == NULL)
	{
		free(p);
		return (NULL);
	}
	p->envp = sh->envp;
	return (p);
}

int			process_execute(t_shell *sh, t_process *p)
{
	int		r;
	static int	(*builtin_functions[]) (t_shell *, char **) = {&builtin_echo,
		&builtin_cd, &builtin_setenv, &builtin_unsetenv, &builtin_env,
		&builtin_exit, &builtin_help};

	if (p->argv[0] != NULL)
	{
		if ((r = builtin_cmd_index(p->argv[0])) != -1)
		{
			p->exit_code = builtin_functions[r](sh, p->argv);
		}
		else
		{
			p->exit_code = execute_external_cmd(sh, p);
		}
		return (p->exit_code);
	}
	return (EXIT_FAILURE);
}

void		execute(t_shell *sh, char *cmd)
{
	t_process	*p;

	p = process_prepare(sh, cmd);
	if (p != NULL)
	{
		p->exit_code = process_execute(sh, p);
		sh->exit_code = p->exit_code;
		(void)process_destroy(p);
	}
	return ;
}

int			main(int argc, char **argv, char **envp)
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
		if (ft_strlen(sh->buffer) != 0)
		{
				
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
//		    print_trees(ast);

			t_ast	*ptr;
			t_ast	*right;

			int i;

			i = 0;
			while (ast[i] != NULL)
			{
			ptr = ast[i];
			int ec2;

			while (ptr->next)
				ptr = ptr->next;	//go to last command

			int ec;
			ec = 0;
			t_process *p = process_prepare(sh, ptr->name);
			if (p != NULL)
			{
				ec = process_execute(sh, p);
				(void)process_destroy(p);
			}

			ptr = ptr->parent;

			while (ptr)	//backtrack till we get to first node
			{

					if (ptr->type == OP_AND)
					{
						if (ec == 0)	//success
						{
							right = ptr->right;
							p = process_prepare(sh, right->name);
							if (p != NULL)
							{
								ec2 = process_execute(sh, p);
								(void)process_destroy(p);				
								if (ec2 != 0)
									ec = 1;		//if second command failed, expression is false, 1
							}
						}

					}
					else if (ptr->type == OP_OR)
					{
						if (ec != 0)
						{
							right = ptr->right;
							p = process_prepare(sh, right->name);
							if (p != NULL)
							{
								ec2 = process_execute(sh, p);
								(void)process_destroy(p);
								if (ec2 == 0)
									ec = 0;	//if second command is successful, then expression is true, success, 0
							}
						}
					}
					ptr = ptr->parent;

			}
			sh->exit_code = ec;
			i++;

			}

		    free_ast(lex);
		    free_trees(ast);
///////////////////////////////////
	
//			execute(sh, sh->buffer);

		}
		clear_input_buffers(sh);
	}
	clean_up(sh);
	return (0);
}
