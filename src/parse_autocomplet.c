/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_autocomplet.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:32:05 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/07 02:14:10 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parse.h"

t_autocomplet	type_to_complet(char *str)
{
	char	*cpy;

	if (!str)
		return (PROG);
	str = ft_strrev(str);
	cpy = str;
	if (str && *str && *str != ' ' && *str != '\t')
		while (str && *str && *str != ' ' && *str != '\t' && *str != '\'' &&
		*str != '"' && *str != '|' && *str != '!' && *str != ';' && *str != '&')
			str++;
	while (str && *str && (*str == ' ' || *str == '\t'))
		str++;
	if (!ft_strlen(str) || (str && (*str == '!' || *str == '|' || *str == ';'
		|| (*str == '&' && str[1] && str[1] == '&'))))
	{
		ft_strdel(&cpy);
		return (PROG);
	}
	ft_strdel(&cpy);
	return (FICHIER);
}
