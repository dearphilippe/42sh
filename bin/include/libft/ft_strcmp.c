/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 04:30:11 by brabo-hi          #+#    #+#             */
/*   Updated: 2017/11/14 22:45:49 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		ft_strcmp_withspace(const char *s1, const char *s2)
{
	while (s1 && *s1 && *s1 == ' ')
		s1++;
	while (s2 && *s2 && *s2 == ' ')
		s2++;
	return (ft_strcmp(s1, s2));
}