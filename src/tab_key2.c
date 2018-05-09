/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_key2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:09:15 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/09 01:09:16 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int		word_length_backwards(char *right, char *boundary)
{
	int i;

	if ((right == NULL) || (boundary == NULL))
		return (0);
	i = 0;
	while (&right[0 - i] > boundary)
	{
		if (right[0 - i] == '\n')
		{
			boundary = &right[0 - i + 1];
			break ;
		}
		i++;
	}
	i = 0;
	while (&right[0 - i] > boundary)
	{
		if (ft_isspace(right[0 - i]))
			break ;
		i++;
	}
	if (&right[0 - i] == boundary)
		return (right - boundary + 1);
	return (i);
}

int		tab_all_commands_longer(t_shell *sh, t_exec **a)
{
	size_t	k_len;
	int		i;
	size_t	j;

	i = 0;
	j = word_length_backwards(&sh->buffer[sh->buf_i - 1], sh->buffer);
	while (a[i] != NULL)
	{
		k_len = ft_strlen(basename(a[i]->cmd));
		if (k_len <= j)
			return (0);
		i++;
	}
	return (1);
}

int		tab_mini_complete(t_shell *sh, t_exec **a)
{
	char	c;
	int		i_len;

	if (tab_all_commands_longer(sh, a) == 1)
	{
		i_len = word_length_backwards(&sh->buffer[sh->buf_i - 1], sh->buffer);
		if (i_len == 0)
			return (0);
		c = basename(a[0]->cmd)[i_len];
		if ((c) && (tab_all_commands_share_letter(a, i_len, c) == 1))
		{
			(void)insert_character(&sh->buffer[sh->buf_i], c);
			sh->input_size++;
			sh->buf_i++;
			reprint_input(sh);
			return (1 + tab_mini_complete(sh, a));
		}
	}
	return (0);
}

char	*insert_string(char *parent, char *child)
{
	char	*tail;
	int		i;

	if ((parent == NULL) || (child == NULL))
		return (NULL);
	tail = ft_strdup(parent);
	ft_strcpy(parent, child);
	i = ft_strlen(parent) - 1;
	ft_strcpy(&parent[i], tail);
	free(tail);
	return (parent);
}

int		key_tab_function_3(t_shell *sh, char *str)
{
	sh->last_word = key_tab_last_word(str);
	if (sh->search_path != NULL)
		free(sh->search_path);
	sh->search_path = ft_strdup(".");
	return (ft_strlen(sh->last_word) - 1);
}
