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
