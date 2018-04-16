/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:51:05 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 17:03:00 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
