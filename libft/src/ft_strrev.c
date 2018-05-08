/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:31:08 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/06 21:31:16 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*out;
	int		i;

	i = ft_strlen(str);
	if (!(out = (char *)ft_memalloc(sizeof(char) * i + 1)))
		return (NULL);
	if (i)
	{
		out[i--] = '\0';
		while (str && *str)
			out[i--] = *str++;
	}
	return (out);
}
