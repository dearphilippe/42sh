/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_files_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 00:48:58 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/09 00:48:59 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int		tab_files_array_of_matches_help1(char ***a, char *search, int *len)
{
	*a = ft_memalloc(sizeof(char *) * (*len + 1));
	*len = ft_strlen(search);
	return (0);
}

char	**tab_files_array_of_matches_help2(char **a, DIR *dirp, int i)
{
	a[i] = NULL;
	(void)closedir(dirp);
	return (a);
}

void	tab_files_array_of_matches_1(t_shell *sh, char **a, int i)
{
	tab_bubble_sortf(a, i);
	tab_files_mini_complete(sh, a);
	tab_print_columnsf(a, i);
}

void	tab_files_array_of_matches_2(t_shell *sh)
{
	insert_character(&sh->buffer[sh->buf_i], ' ');
	sh->buf_i++;
	sh->input_size++;
}

void	tab_files_array_of_matches_3(t_shell *sh, char **a, int *i)
{
	insert_character(&sh->buffer[sh->buf_i], a[0][*i]);
	(*i)++;
	sh->buf_i++;
	sh->input_size++;
}
