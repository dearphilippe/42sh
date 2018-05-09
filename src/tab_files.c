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

int		tab_files_valid_directory(char *path)
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

int		tab_files_count_match_in_dir(char *path, char *search)
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
		i = tab_files_array_of_matches_help1(&a, search, &len);
		while ((dp = readdir(dirp)) != NULL)
		{
			if ((len == 0) && (ft_strcmp(".", dp->d_name) == 0))
				continue ;
			if ((len == 0) && (ft_strcmp("..", dp->d_name) == 0))
				continue ;
			if (ft_strncmp(search, dp->d_name, len) == 0)
				a[i++] = tab_files_copy_filename(path, dp);
		}
		return (tab_files_array_of_matches_help2(a, dirp, i));
	}
	return (NULL);
}
