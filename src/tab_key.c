/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:25:17 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/08 21:22:00 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

t_exec	**tab_array_of_matches(t_shell *sh, char *str)
{
	t_exec	**result;
	t_exec	*ptr;
	int		count;
	int		i;
	int		needle_len;

	count = tab_count_matches(sh, str);
	result = ft_memalloc((count + 1) * sizeof(t_exec *));
	i = 0;
	ptr = sh->exec;
	needle_len = ft_strlen(str);
	while (i < count)
	{
		if (ft_strncmp(str, basename(ptr->cmd), needle_len) == 0)
			result[i++] = ptr;
		ptr = ptr->next;
	}
	result[i] = NULL;
	return (result);
}

void	tab_remove_duplicates(t_exec **array, int *count)
{
	int		i;
	int		k;
	char	*a;
	char	*b;

	i = 0;
	while (i < *count - 1)
	{
		a = basename(array[i]->cmd);
		b = basename(array[i + 1]->cmd);
		if (ft_strcmp(a, b) == 0)
		{
			k = i + 1;
			while (k < *count)
			{
				array[k] = array[k + 1];
				k++;
			}
			array[k] = NULL;
			(*count)--;
			continue;
		}
		i++;
	}
}

/*
** returns input from beginning (or newline) till current cursor position
*/

char	*key_tab_part_str(t_shell *sh)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	if (sh->input_size > 0)
	{
		i = sh->input_size;
		while ((i >= 0) && (sh->buffer[i] != '\n'))
			i--;
		i++;
		if ((int)sh->buf_i >= i)
		{
			result = ft_memalloc(sh->buf_i - i + 1);
			ft_memcpy(result, &sh->buffer[i], sh->buf_i - i);
		}
	}
	return (result);
}

char	*key_tab_last_word(char *str)
{
	int	i;

	if (str == NULL)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (i > 0)
	{
		if (ft_isspace(str[i]))
		{
			if ((i > 0) && (str[i - 1] == '\\'))
			{
				i--;
				continue ;
			}
			else
			{
				i++;
				break ;
			}
		}
		i--;
	}
	return (&str[i]);
}

char	*insert_character(char *dst, char c)
{
	int i;

	if (dst == NULL)
		return (NULL);
	i = ft_strlen(dst);
	while (i >= 0)
	{
		dst[i + 1] = dst[i];
		i--;
	}
	dst[0] = c;
	return (dst);
}

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
		{
//			i++;
			break ;
		}
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

void	key_tab_function(t_shell *sh)
{
	t_exec	**matches;
	int		i;
	t_autoc	bachir;
	char	*str;

	sh->last_word = NULL;

	if ((str = key_tab_part_str(sh)) == NULL)
		return ;

	bachir = type_to_complet(str);
//	ft_printf(1, "type_to_complet(), str = [%s], returns %d\n", str, bachir);

	if ((sh->input_size > 0) && (bachir == PROG))
	//		(type_to_complet(key_tab_part_str(sh)) == PROG))
//			(string_has_whitespace(sh->buffer) == 0))
	{
		sh->last_word = key_tab_last_word(str);

		matches = tab_array_of_matches(sh, sh->last_word);
		i = tab_count_matches(sh, sh->last_word);
		tab_bubble_sort(matches, i);
		tab_remove_duplicates(matches, &i);
		if (i == 1)
		{

//			(void)insert_string(&sh->buffer[sh->buf_i], basename(matches[0]->cmd));
//			sh->buf_i += ft_strlen(basename(matches[0]->cmd));
//			(void)insert_string(&sh->buffer[sh->buf_i], " ");
//			sh->buf_i++;
//			sh->input_size += ft_strlen(basename(matches[0]->cmd)) + 1;
//			tab_mini_complete(sh, matches);
			int	k = 0;
			char *match = basename(matches[0]->cmd);
			sh->buf_i -= ft_strlen(sh->last_word);
			while ((match[k]) && (match[k] == sh->buffer[sh->buf_i]))
			{
				k++;
				sh->buf_i++;
			}
			while (match[k] != 0)
			{
				insert_character(&sh->buffer[sh->buf_i], match[k]);
				sh->buf_i++;
				sh->input_size++;
				k++;
			}
			insert_character(&sh->buffer[sh->buf_i], ' ');
			sh->buf_i++;
			sh->input_size++;

//			sh->buf_i++;
//			sh->input_size++;


/*
			ft_strcpy(&sh->buffer[sh->buf_i], basename(matches[0]->cmd)); // XXX
			sh->buf_i = ft_strlen(basename(matches[0]->cmd));
			sh->buffer[sh->buf_i++] = ' ';
			sh->input_size = sh->buf_i;
*/			reprint_input(sh);

		}
		else if ((i > 1) && (tab_mini_complete(sh, matches) == 0))
		{
			tab_print_columns(matches, i);
			reprint_input(sh);

		}
		free(matches);
	}
	if ((sh->input_size > 0) && (bachir == FICHIER))
	{
		sh->last_word = key_tab_last_word(str);
/*
		if (tab_files_valid_directory(sh->last_word))
		{
			if (sh->search_path != NULL)
				free(sh->search_path);
			sh->search_path = ft_strdup(sh->last_word);
			sh->last_word = EMPTY_STRING;
//			tab_files_show_columns(sh, sh->search_path, "");
		}
		else
		{
*/

			if (sh->search_path != NULL)
				free(sh->search_path);
			sh->search_path = ft_strdup(".");


			int f = ft_strlen(sh->last_word) - 1;
			int g;
			while (&sh->last_word[f] >= sh->last_word)
			{
				if (sh->last_word[f] == '/')
				{
					free(sh->search_path);
					g = &sh->last_word[f] - sh->last_word;
					if (!g)
						g++;
					sh->search_path = ft_memalloc(g + 1);
					(void)ft_memcpy(sh->search_path, sh->last_word, g);
					sh->last_word = &sh->last_word[f + 1];
	
					break ;
				}
				f--;
			}



		tab_files_show_columns(sh, sh->search_path, sh->last_word);
		reprint_input(sh);


	}

	free(str);
	return ;
}
