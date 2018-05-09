/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_key3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 01:12:13 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/09 05:23:16 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

void	key_tab_function(t_shell *sh)
{
	int		f;
	t_autoc	bachir;
	char	*str;

	sh->last_word = NULL;
	if ((str = key_tab_part_str(sh)) == NULL)
		return ;
	bachir = type_to_complet(str);
	if ((sh->input_size > 0) && (bachir == PROG))
		key_tab_function_2(sh, str);
	if ((sh->input_size > 0) && (bachir == FICHIER))
	{
		f = key_tab_function_3(sh, str);
		while (&sh->last_word[f] >= sh->last_word)
		{
			if (sh->last_word[f] == '/' && key_tab_function_1(sh, f))
				break ;
			f--;
		}
		tab_files_show_columns(sh, sh->search_path, sh->last_word);
		reprint_input(sh);
	}
	free(str);
	return ;
}

void	insert_character_1(t_shell *sh, char *s, char c)
{
	insert_character(s, c);
	sh->buf_i++;
	sh->input_size++;
}

int		key_tab_function_1(t_shell *sh, int f)
{
	int		g;

	free(sh->search_path);
	g = &sh->last_word[f] - sh->last_word;
	if (!g)
		g++;
	sh->search_path = ft_memalloc(g + 1);
	(void)ft_memcpy(sh->search_path, sh->last_word, g);
	sh->last_word = &sh->last_word[f + 1];
	return (1);
}

void	key_tab_function_2b(t_shell *sh, int *k)
{
	(*k) += 1;
	sh->buf_i += 1;
	return ;
}

void	key_tab_function_2(t_shell *sh, char *str)
{
	t_exec	**matches;
	char	*match;
	int		i;
	int		k;

	sh->last_word = key_tab_last_word(str);
	matches = tab_array_of_matches(sh, sh->last_word);
	i = tab_count_matches(sh, sh->last_word);
	tab_bubble_sort(matches, i);
	tab_remove_duplicates(matches, &i);
	if (i == 1)
	{
		k = 0;
		match = basename(matches[0]->cmd);
		sh->buf_i -= ft_strlen(sh->last_word);
		while ((match[k]) && (match[k] == sh->buffer[sh->buf_i]))
			key_tab_function_2b(sh, &k);
		while (match[k] != 0)
			insert_character_1(sh, &sh->buffer[sh->buf_i], match[k++]);
		insert_character_1(sh, &sh->buffer[sh->buf_i], ' ');
	}
	else if ((i > 1) && (tab_mini_complete(sh, matches) == 0))
		tab_print_columns_1(sh, matches, i);
	free(matches);
	reprint_input(sh);
}
