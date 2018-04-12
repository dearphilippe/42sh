/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:43:16 by passef            #+#    #+#             */
/*   Updated: 2018/04/11 13:49:14 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int ac, char const * const *av)
{
	char	*var;
	int		i;

	i = 0;

	if (ac > 1)
		var = getenv(av[1]);

	if (!var)
		printf("n'existe pas\n");
	else
		printf("%s : %s\n", av[1], var);

	return (0);
}