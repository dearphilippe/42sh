/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:07:25 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 15:14:41 by ztisnes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*remove_start_space(char *str)
{
	char	*dest;

	if (!str)
		return (NULL);
	while (str && *str && *str == ' ')
		str++;
	if (!(dest = ft_memalloc(ft_strlen(str) + 1)))
		return (NULL);
	return (ft_strcpy(dest, str));
}

char	*delete_backslash_in_double_quote(char *str)
{
	char	*dest;
	int		i;

	if (!ft_strlen(str) ||
			!(dest = (char *)ft_memalloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	while (str && *str)
	{
		if (*str == '\\' && str++)
		{
			if (!str || !*str)
				return (NULL);
			if (*str == 'a')
				dest[i++] = 7;
			else if (*str == 'b')
				dest[i++] = 8;
			else if (*str == 'f')
				dest[i++] = 12;
			else if (*str == 'n')
				dest[i++] = 10;
			else if (*str == 'r')
				dest[i++] = 13;
			else if (*str == 't')
				dest[i++] = 9;
			else if (*str == 'v')
				dest[i++] = 11;
			else if (*str == '\\')
				dest[i++] = 92;
			else if (*str == '\'')
				dest[i++] = 39;
			else if (*str == '"')
			{
				dest[i++] = '\\';
				dest[i++] = 34;
			}
			else
			{
				dest[i++] = '\\';
				dest[i++] = *str;
			}
			str++;
			continue ;
		}
		dest[i++] = *str;
		str++;
	}
	dest[i] = '\0';
	return (dest);
}
