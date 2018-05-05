/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:11:37 by asarandi          #+#    #+#             */
/*   Updated: 2018/04/15 20:12:12 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

char		*ft_str_append(char *str, char c)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(out = ft_strnew(ft_strlen(str) + 2)))
		return (NULL);
	while (str && str[j])
		out[i++] = str[j++];
	out[i++] = c;
	out[i] = '\0';
	ft_strdel(&str);
	return (out);
}
