/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:45:40 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/08 03:12:40 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int	tab_files_valid_directory(char *path)
{
	struct stat	st;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
				return (1);
		}
	}
	return (0);
}

int	tab_files_count_match_in_dir(char *path, char *search)
{
	int				r;
	int				len;
	DIR				*dirp;
	struct dirent	*dp;

	if (tab_files_valid_directory(path) == 1)
	{
		if ((dirp = opendir(path)) == NULL)
			return (0);
		len = ft_strlen(search);
		r = 0;
		while ((dp = readdir(dirp)) != NULL)
		{
			if (ft_strncmp(search, dp->d_name, len) == 0)
				r++;
			if ((len == 0) && (ft_strcmp(".", dp->d_name) == 0))
				r--;
			if ((len == 0) && (ft_strcmp("..", dp->d_name) == 0))
				r--;
		}
		(void)closedir(dirp);
		return (r);
	}
	return (0);
}

char	*tab_files_copy_filename(char *path, struct dirent *dp)
{
	char		*filename;
	char		*result;
	int			len;
	struct stat	st;

	filename = dir_slash_exec(path, dp->d_name);
	len = ft_strlen(dp->d_name);
	stat(filename, &st);
	if (S_ISDIR(st.st_mode))
		len++;
	result = ft_memalloc(len + 1);
	result = ft_strcpy(result, dp->d_name);
	if (S_ISDIR(st.st_mode))
		result[len - 1] = '/';
	free(filename);
	return (result);
}

char	**tab_files_array_of_matches(char *path, char *search)
{
	char			**a;
	int				len;
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	if (tab_files_valid_directory(path) == 1)
	{
		if ((dirp = opendir(path)) == NULL)
			return (NULL);
		len = tab_files_count_match_in_dir(path, search);
		a = ft_memalloc(sizeof(char *) * (len + 1));
		len = ft_strlen(search);
		i = 0;
		while ((dp = readdir(dirp)) != NULL)
		{
			if ((len == 0) && (ft_strcmp(".", dp->d_name) == 0))
				continue ;
			if ((len == 0) && (ft_strcmp("..", dp->d_name) == 0))
				continue ;
			if (ft_strncmp(search, dp->d_name, len) == 0)
				a[i++] = tab_files_copy_filename(path, dp);//ft_strdup(dp->d_name);
		}
		a[i] = NULL;
		(void)closedir(dirp);
		return (a);
	}
	return (NULL);
}

int		word_length_backwardsf(char *right, char *boundary)
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
				{
					insert_character(&sh->buffer[sh->buf_i], a[0][i]);
					i++;
					sh->buf_i++;
					sh->input_size++;
				}
				if (sh->buffer[sh->buf_i - 1] != '/')
				{			
					insert_character(&sh->buffer[sh->buf_i], ' ');
					sh->buf_i++;
					sh->input_size++;
				}
//					reprint_input(sh);
			}
			else
			{
				tab_bubble_sortf(a, i);
				tab_files_mini_complete(sh, a);
				tab_print_columnsf(a, i);
			}
			destroy_char_array(a);
		}
	}
	return ;
}
