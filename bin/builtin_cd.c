/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhernand <lhernand@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 00:49:02 by lhernand          #+#    #+#             */
/*   Updated: 2018/04/06 01:40:24 by lhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf_header.h"
#include "../ft_printf/ft_struct.h"

static void	inititalize(char *flags[])
{
	*flags = {"", "-L", ".", "..", "/",  };
}

int			builtin_cd(char **params)
{
    
	return (0);
}

int		main(void)
{
	ft_printf("what the fuck\n");
	return (0);
}
