/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/04/15 05:28:21 by ztisnes          ###   ########.fr       */
=======
/*   Updated: 2018/04/14 20:27:12 by asarandi         ###   ########.fr       */
>>>>>>> c2dffcec1eb6007c98ac0d447d7d8abb83e7d2e4
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

int		ast_is_ambiguous(t_ast *ast)
<<<<<<< HEAD
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

t_ast		**ast_create_tree(char *str)
{
	t_ast	*lex;
	t_ast	**ast;
=======
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

int		group_process_wait(t_process **group)
{
	int i;
	int pid;
	int	status;

	pid = 0;
	status = 0;
	while ((pid = wait(&status)) != -1)	/* pick up all the dead children */
	{
		i = 0;
		while (group[i])
		{
			if (group[i]->pid == pid)
			{
				group[i]->exit_code = WEXITSTATUS(status);	
				break ;
			}
			i++;
		}
	}
	i = 0;
	while (group[i] != NULL)
	{
		status = group[i]->exit_code;
		ft_printf(1, "{cyan} pid = %d, exit code = %d{eoc}\n", group[i]->pid, status);
		i++;
	}
	return (status);
}

void	group_fork_exec(t_process *p, int i, int count, int *pipes)
{
	if ((p->pid = fork()) == 0)
	{
		if (i < count - 1)
			dup2(pipes[(i * 2) + 1], 1);
		if ((i > 0) && (i < count))
			dup2(pipes[(i * 2) - 2], 0);
		i = 0;
		while (i < count - 1)
		{
			close(pipes[i * 2]);
			close(pipes[(i * 2) + 1]);
			i++;
		}
		execve(p->fullpath, p->argv, p->envp);
	}
	else if (p->pid == -1)
		(void)fatal_error_message(g_sh, E_FORK);
	return ;
}

int		group_process_execute(t_shell *sh, t_process **group)
{
	int		i;
	char	*path;
	char	*fullpath;
	int		count;
	int		*pipes;

	i = 0;
	while (group[i] != NULL)
		i++;
	count = i;
	pipes = ft_memalloc((count) * 2 * sizeof(int));
	i = 0;
	while (i < count - 1)
	{
		pipe(pipes + (i * 2));
		i++;
	}
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
		(void)group_fork_exec(group[i], i, count, pipes);
		i++;
	}
	i = 0;
	while (i < count - 1)
	{
		close(pipes[i * 2]);
		close(pipes[(i * 2) + 1]);
		i++;

	}
	return (0);
}
>>>>>>> c2dffcec1eb6007c98ac0d447d7d8abb83e7d2e4

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
	free_ast(lex);
	return (ast);
}

void	group_process_destroy(t_process **group)
{
	int	i;

<<<<<<< HEAD
	i = 0;
	while (group[i] != NULL)
	{
		(void)process_destroy(group[i]);
		i++;
	}
	free(group);
	return ;
}

int			group_process_wait(t_process **group)
{
	int		i;
	int		pid;
	int		status;

	pid = 0;
	status = 0;
	while ((pid = wait(&status)) != -1)	/* pick up all the dead children */
	{
		i = 0;
		while (group[i])
		{
			if (group[i]->pid == pid)
			{
				group[i]->exit_code = WEXITSTATUS(status);
				break ;
			}
			i++;
		}
	}
	i = 0;
	while (group[i] != NULL)
	{
		status = group[i]->exit_code;
		ft_printf(1, "{cyan} pid = %d, exit code = %d{eoc}\n", group[i]->pid, status);
		i++;
	}
	return (status);
}

void		group_fork_exec(t_process *p, int i, int count, int *pipes)
{
	if ((p->pid = fork()) == 0)
	{
		if (i < count - 1)
			dup2(pipes[(i * 2) + 1], 1);
		if ((i > 0) && (i < count))
			dup2(pipes[(i * 2) - 2], 0);
		i = 0;
		while (i < count - 1)
		{
			close(pipes[i * 2]);
			close(pipes[(i * 2) + 1]);
			i++;
		}
		execve(p->fullpath, p->argv, p->envp);
	}
	else if (p->pid == -1)
		(void)fatal_error_message(g_sh, E_FORK);
	return ;
}

int			group_process_execute(t_shell *sh, t_process **group)
{
	int		i;
	char	*path;
	char	*fullpath;
	int		count;
	int		*pipes;

	i = 0;
	while (group[i] != NULL)
		i++;
	count = i;
	pipes = ft_memalloc((count) * 2 * sizeof(int));
	i = 0;
	while (i < count - 1)
	{
		pipe(pipes + (i * 2));
		i++;
	}
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
		(void)group_fork_exec(group[i], i, count, pipes);
		i++;
	}
	i = 0;
	while (i < count - 1)
	{
		close(pipes[i * 2]);
		close(pipes[(i * 2) + 1]);
		i++;

	}
	return (0);
}

int				main(int argc, char **argv, char **envp)
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
//								int i = 0;
//								while (group[i] != NULL)
//									i++;
//								while (i--)
								(void)group_process_wait(group);
								(void)group_process_destroy(group);
								tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_custom);

							}
							else
							{

							}
=======
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
//								int i = 0;
//								while (group[i] != NULL)
//									i++;
//								while (i--)
								(void)group_process_wait(group);
								(void)group_process_destroy(group);
								tcsetattr(STDIN_FILENO, TCSANOW, &sh->t_custom);



							}
							else
							{

							}
>>>>>>> c2dffcec1eb6007c98ac0d447d7d8abb83e7d2e4
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
<<<<<<< HEAD
									(void)process_destroy(p);
=======
									(void)process_destroy(p);				
>>>>>>> c2dffcec1eb6007c98ac0d447d7d8abb83e7d2e4
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
<<<<<<< HEAD

=======
						
>>>>>>> c2dffcec1eb6007c98ac0d447d7d8abb83e7d2e4
							}
						}
						if (ptr != NULL)
							ptr = ptr->parent;
					}
				}
				i++;
			}
			sh->exit_code = ec;
<<<<<<< HEAD
			free_trees(ast);
=======
		    free_trees(ast);
>>>>>>> c2dffcec1eb6007c98ac0d447d7d8abb83e7d2e4
		}
		clear_input_buffers(sh);
	}
	clean_up(sh);
	return (0);
}
