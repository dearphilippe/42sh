/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:29:17 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/06 06:02:02 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dir_slash_exec(char *dir, char *cmd)
{
	char	*result;
	char	*folder;

	if (dir == NULL)
		dir = EMPTY_STRING;
	if ((ft_strlen(dir) > 0) && (dir[ft_strlen(dir) - 1] != '/'))
		folder = ft_strjoin(dir, "/");
	else
		folder = ft_strdup(dir);
	result = ft_strjoin(folder, cmd);
	free(folder);
	return (result);
}

int		is_fullpath_provided(char *fullpath)
{
	if (access(fullpath, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

int		path_has_executable(char *path, char *cmd)
{
	char	*fullpath;
	int		result;

	fullpath = dir_slash_exec(path, cmd);
	result = 0;
	if (access(fullpath, F_OK | X_OK) == 0)
		result = 1;
	free(fullpath);
	return (result);
}

char	*find_command_path(t_shell *sh, char *cmd)
{
	char	**folders;
	char	*path;
	char	*result;
	int		i;

	if ((path = kv_array_get_key_value(sh->envp, "PATH")) == NULL)
		return (NULL);
	if ((folders = ft_strsplit(path, ':')) == NULL)
		fatal_error_message(sh, E_NOMEM);
	i = 0;
	result = NULL;
	while (folders[i])
	{
		if (path_has_executable(folders[i], cmd) == 1)
		{
			result = ft_strdup(folders[i]);
			break ;
		}
		i++;
	}
	destroy_char_array(folders);
	return (result);
}
