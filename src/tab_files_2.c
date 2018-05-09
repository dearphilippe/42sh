/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_files_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 00:40:48 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/09 00:40:49 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int		word_length_backwardsf(char *right, char *boundary)
{
	int i;

	if (!(i = 0) && ((right == NULL) || (boundary == NULL)))
		return (0);
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
		if ((ft_isspace(right[0 - i])) && (right[0 - i - 1] != '\\'))
			break ;
		if ((right[0 - i] == '/') && (right[0 - i - 1] != '\\'))
			break ;
		i++;
	}
	if (&right[0 - i] == boundary)
		return (right - boundary + 1);
	return (i);
}

int		tab_files_all_names_longer(t_shell *sh, char **a)
{
	size_t	k_len;
	int		i;
	size_t	j;

	i = 0;
	j = word_length_backwardsf(&sh->buffer[sh->buf_i - 1], sh->buffer);
	while (a[i] != NULL)
	{
		k_len = ft_strlen(a[i]);
		if (k_len <= j)
			return (0);
		i++;
	}
	return (1);
}

int		tab_files_all_names_share_letter(char **a, int index, char c)
{
	int		i;

	i = 0;
	while (a[i] != NULL)
	{
		if (a[i][index] != c)
			return (0);
		i++;
	}
	return (1);
}

int		tab_files_mini_complete(t_shell *sh, char **a)
{
	char	c;
	int		i_len;

	if (tab_files_all_names_longer(sh, a) == 1)
	{
		i_len = word_length_backwardsf(&sh->buffer[sh->buf_i - 1], sh->buffer);
		if (i_len == 0)
			return (0);
		c = a[0][i_len];
		if ((c) && (tab_files_all_names_share_letter(a, i_len, c) == 1))
		{
			(void)insert_character(&sh->buffer[sh->buf_i], c);
			sh->input_size++;
			sh->buf_i++;
			reprint_input(sh);
			return (1 + tab_files_mini_complete(sh, a));
		}
	}
	return (0);
}

void	tab_files_show_columns(t_shell *sh, char *path, char *search)
{
	int		i;
	char	**a;

	i = tab_files_count_match_in_dir(path, search);
	if (i > 0)
	{
		a = tab_files_array_of_matches(path, search);
		if (a != NULL)
		{
			if (i == 1)
			{
				i = ft_strlen(sh->last_word);
				while (a[0][i])
					tab_files_array_of_matches_3(sh, a, &i);
				if (sh->buffer[sh->buf_i - 1] != '/')
					tab_files_array_of_matches_2(sh);
			}
			else
				tab_files_array_of_matches_1(sh, a, i);
			destroy_char_array(a);
		}
	}
	return ;
}
