/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:57:11 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/06 08:02:56 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_av_buffers(t_av *av)
{
	if (av->out != NULL)
		free(av->out);
	if (av->key != NULL)
		free(av->key);
	free(av);
	return ;
}

t_av	*init_av_buffers(t_shell *sh)
{
	t_av	*av;

	sh->child_argv = ft_memalloc(sizeof(char *));
	sh->child_argv[0] = NULL;
	if ((av = ft_memalloc(sizeof(t_av))) == NULL)
		return (NULL);
	av->in = sh->buffer;
	if ((av->out = ft_memalloc(PAGE_SIZE * 2)) == NULL)
	{
		cleanup_av_buffers(av);
		return (NULL);
	}
	if ((av->key = ft_memalloc(PAGE_SIZE)) == NULL)
	{
		cleanup_av_buffers(av);
		return (NULL);
	}
	av->val = NULL;
	return (av);
}

void	add_string_to_child_argv(t_shell *sh, char *str, int *k)
{
	char **old_array;
	char *new_string;

	if ((str == NULL) || (str[0] == 0))
		return ;
	str[*k] = 0;
	*k = 0;
	old_array = sh->child_argv;
	new_string = ft_strdup(str);
	sh->child_argv = add_element_to_char_array(sh->child_argv, new_string);
	destroy_char_array(old_array);
	return ;
}

int		build_child_argv_list(t_shell *sh, int i, int k, int sub_op)
{
	t_av	*av;

	if ((av = init_av_buffers(sh)) == NULL)
		return (0);
	while ((av->in[i]) && (ft_isspace(av->in[i])))
		i++;
	while (av->in[i])
	{
		if (av->in[i] == STRONG_QUOTE)
			sub_op = handle_strong_quote(av, &i, &k);
		else if (av->in[i] == WEAK_QUOTE)
			sub_op = handle_weak_quote(av, sh, &i, &k);
		else if ((av->in[i] == DOLLAR_SIGN) && (ft_isalpha(av->in[i + 1])))
			sub_op = handle_dollar_sign(av, sh, &i, &k);
		else if ((av->in[i] == BACKSLASH) && (i++))
			av->out[k++] = av->in[i++];
		else
			av->out[k++] = av->in[i++];
		if (sub_op == 0)
			return (0);
		if ((ft_isspace(av->in[i])) || (av->in[i] == 0))
			add_string_to_child_argv(sh, av->out, &k);
		while ((av->in[i]) && (ft_isspace(av->in[i])))
			i++;
	}
	cleanup_av_buffers(av);
	return (1);
}
