/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 20:19:02 by passef           ###   ########.fr       */
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

void		process_destroy(t_process *p)
{
	if (p->argv != NULL)
		destroy_char_array(p->argv);
	if (p->fullpath != NULL)
		free(p->fullpath);
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

void	execute(t_shell *sh, char *cmd)
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

int		ast_ambiguous_error(char *msg)
{
	ft_printf(STDERR_FILENO, msg);
	return (1);
}

// ast error checking,
// if > or >> is followed by | display error message "Ambiguous output redirect."
// if | is followed by < display error message "Ambiguous input redirect."

int		ast_is_ambiguous(t_ast *ast)
{
	t_ast	*ptr;

	ptr = ast;
	while (ptr->next)
		ptr = ptr->next;	//go to last command
	ptr = ptr->parent;

	while ((ptr) && (ptr->parent))
	{
		if ((ptr->type == RED_PIPE) && (ptr->parent->type == RED_PREV))
			return (ast_ambiguous_error("Ambiguous input redirect.\n"));
		if ((ptr->type == RED_NEXT) && (ptr->parent->type == RED_PIPE))
			return (ast_ambiguous_error("Ambiguous output redirect.\n"));
		if ((ptr->type == RED_NNEXT) && (ptr->parent->type == RED_PIPE))
			return (ast_ambiguous_error("Ambiguous output redirect.\n"));
		ptr = ptr->parent;
	}
	return (0);
}

t_ast	**ast_create_tree(char *str)
{
	t_ast	*lex;
	t_ast	**ast;

	if ((lex = parse_lexer(str)) == NULL)
	{
		ft_printf(STDERR_FILENO, "ast lexical error!\n");
		return (NULL);
	}
    if (!(ast = (t_ast **)ft_memalloc(sizeof(t_ast *) * get_nbr_instructions(lex) + 1)))
    {
		free_ast(lex);
        ft_printf(STDERR_FILENO, "ast memory error!\n");
		return (NULL);
    }
    if (!(ast = parse_ast(ast, lex)))
	{
		free_ast(lex);
		free_trees(ast);
        ft_printf(STDERR_FILENO, "ast syntax error!\n");
		return (NULL);
	}
//	print_trees(ast);
	free_ast(lex);
	return (ast);
}

void	group_process_destroy(t_process **group)
{
	int	i;

	i = 0;
	while (group[i] != NULL)
	{
		(void)process_destroy(group[i]);
		i++;
	}
	free(group);
	return ;
}

/*
int		fork_exec_wait(t_shell *sh, t_process *p, char *fullpath)
{
	if ((p->pid = fork()) == -1)
		fatal_error_message(sh, E_FORK);
	else if (p->pid == 0)
		execve(fullpath, p->argv, p->envp);
	if (waitpid(p->pid, &p->status, 0) == -1)
	{
		(void)perror(SHELL_NAME);
		return (1);
	}
	if (WIFEXITED(p->status))
		p->exit_code = WEXITSTATUS(p->status);
	return (p->exit_code);
}

int		execute_external_cmd(t_shell *sh, t_process *p)
{
	char	*path;
	char	*fullpath;

	if (is_valid_executable_file(p->argv[0]) == 1)
		return (fork_exec_wait(sh, p, p->argv[0]));
	else
	{
		if ((path = find_command_path(sh, p->argv[0])) == NULL)
		{
			(void)ft_printf(STDERR_FILENO,
					"%s: %s: command not found\n", SHELL_NAME, p->argv[0]);
			p->exit_code = 1;
			return (p->exit_code);	//failure
		}
		fullpath = dir_slash_exec(path, p->argv[0]);
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_original);
		p->exit_code = fork_exec_wait(sh, p, fullpath);
		tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_custom);
		free(path);
		free(fullpath);
	}
	return (p->exit_code);
}
*/
int		group_process_wait(t_process **group)
{
	int i;

	i = 0;
	while (group[i] != NULL)
	{
/*		while ((group[i]->pid = wait(&group[i]->status)) != -1)
		{
			if (group[i + 1] != NULL)
			{
				close(group[i]->fd[0]);
				close(group[i]->fd[1]);
			}

			ft_printf(1, "{green}process [%s], pid %d exits with status %d{eoc}\n", group[i]->argv[0], group[i]->pid, WEXITSTATUS(group[i]->status));
		}
*/		
		
		sleep(1);
		if (group[i + 1] != NULL)
		{
			close(group[i]->fd[0]);
			close(group[i]->fd[1]);
		}
		
		i++;

	}
	return (0);
}

int		group_process_execute(t_shell *sh, t_process **group)
{
	int		i;
	char	*path;
	char	*fullpath;

	i = 0;
	while (group[i])
	{
		if (is_valid_executable_file(group[i]->argv[0]) == 1)
			fullpath = ft_strdup(group[i]->argv[0]);
		else
		{
			if ((path = find_command_path(sh, group[i]->argv[0])) == NULL)
			{
				(void)ft_printf(STDERR_FILENO,
						"%s: %s: command not found\n", SHELL_NAME, group[i]->argv[0]);
				return (1);
			}
			group[i]->fullpath = dir_slash_exec(path, group[i]->argv[0]);
			free(path);
		}
		//pipe
		//fork
		//dup

		if (group[i + 1] != NULL)
			pipe(group[i]->fd);

		group[i]->pid = fork();
		if (group[i]->pid == 0)
		{
			if (i == 0)
				close(group[i]->fd[0]);

			if (group[i + 1] != NULL)
				dup2(group[i]->fd[1], 1);
	
			if (i > 0)
				dup2(group[i - 1]->fd[0], 0);

			if (group[i + 1] == NULL)
				close(group[i - 1]->fd[1]);
//			else
//				close(group[i]->fd[0]);
//			else
//				close(group[i]->fd[0]);
//			if (group[i + 1] == NULL)
//				close(group[i]->fd[0]);
			
			execve(group[i]->fullpath, group[i]->argv, group[i]->envp);
		}
		else if (group[i]->pid == -1)
		{
//			perror(SHELL_NAME);
			fatal_error_message(sh, E_FORK);
			return (1);	//failed to fork
		}
		i++;
	}
	return (0);
}



int		main(int argc, char **argv, char **envp)
{
	t_shell		*sh;
    t_ast		**ast;
	t_ast		*ptr;
	int			i;
	int			ec2;
	int			ec;
	t_process	*p;


	sh = init_shell(argc, argv, envp);
	while (1)
	{
		sh->state = STATE_READ;
		raw_read(sh);
		if (sh->buffer == NULL)
			break ;
		if ((ft_strlen(sh->buffer) != 0) && ((ast = ast_create_tree(sh->buffer)) != NULL))
		{
			i = 0;
			ec = 0;
			while (ast[i] != NULL)
			{
				ptr = ast[i];
				if (ast_is_ambiguous(ptr) == 0)
				{
					while (ptr->next)
						ptr = ptr->next;	//go to last command
					while (ptr)
					{
						if ((ptr->parent) && (IS_RED(ptr->parent->name)))
						{
							//build process group
							ft_printf(1, "parent is a redirection\n");
							if (ptr->next == NULL)	//bottom process
							{
								t_ast	*tmp;
								int		k;
								t_process	**group;

								k = 1;
								tmp = ptr->parent;
								while ((tmp) && (IS_RED(tmp->name)))
								{
									tmp = tmp->parent;
									k += 1;
								}
								group = ft_memalloc(sizeof(t_process *) * (k + 1));

								k = 0;
								group[k++] = process_prepare(sh, ptr->name);
								ptr = ptr->parent;
								while ((ptr) && (IS_RED(ptr->name)))
								{
									group[k++] = process_prepare(sh, ptr->right->name);
									ptr = ptr->parent;
								}

								tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_original);
								(void)group_process_execute(sh, group);
								(void)group_process_wait(group);
								(void)group_process_destroy(group);
								tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_custom);
							}
							else
							{

							}
						}
						else	//single process  or  parent is logical operator
						{
							if ((ptr->next == NULL) && ((p = process_prepare(sh, ptr->name)) != NULL))	//bottom process
							{
								ec = process_execute(sh, p);
								(void)process_destroy(p);
							}
							else
							{
								if ((ptr->type == OP_AND) && (ec == 0) && ((p = process_prepare(sh, ptr->right->name)) != NULL))
								{
									ec2 = process_execute(sh, p);
									(void)process_destroy(p);				
									if (ec2 != 0)
										ec = 1;	//if second command failed, expression is false, 1
								}
								else if ((ptr->type == OP_OR) && (ec != 0) && ((p = process_prepare(sh, ptr->right->name)) != NULL))
								{
									ec2 = process_execute(sh, p);
									(void)process_destroy(p);
									if (ec2 == 0)
										ec = 0;	//if second command is successful, then expression is true, success, 0
								}
						
							}
						}
						if (ptr != NULL)
							ptr = ptr->parent;
					}
				}
				i++;
			}
			sh->exit_code = ec;
		    free_trees(ast);
		}
		clear_input_buffers(sh);
	}
	clean_up(sh);
	return (0);
}
