/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_columns_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 18:27:20 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/07 19:24:20 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

int		tab_max_lengthf(char **array)
{
	int		i;
	int		len;
	int		max_length;

	i = 0;
	max_length = 0;
	while (array[i] != NULL)
	{
		len = ft_strlen(array[i]);
		if (len > max_length)
			max_length = len;
		i++;
	}
	return (max_length);
}

void	tab_bubble_sortf(char **a, int count)
{
	int		i;
	int		flag;
	char	*tmp;

	while (1)
	{
		i = 0;
		flag = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(a[i], a[i + 1]) > 0)
			{
				flag = 1;
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
			i++;
		}
		if (flag == 0)
			break ;
	}
}

void	col_print_loopf(int cw, int nc, int count, char **a)
{
	int	i;
	int j;
	int f;
	int nr;

	nr = 0;
	while (nr * nc < count)
		nr++;
	i = 0;
	while (i < nr)
	{
		j = 0;
		while (j < nc)
		{
			if (i + j * nr < count)
				f = col_print_cmd(a[i + j * nr], j, cw, nc);
			else
				col_if_flag_print_newline(&f);
			j++;
		}
		i++;
	}
	if (f)
		ft_printf(STDOUT_FILENO, "\n");
}

void	tab_print_columnsf(char **array, int count)
{
	int				max_len;
	int				cw;
	struct winsize	ws;
	int				nc;

	count = count_char_array(array);
	ft_printf(STDOUT_FILENO, "\n");
	max_len = tab_max_lengthf(array);
	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		return ;
	cw = max_len + 2;
	nc = ws.ws_col / cw;
	if (nc == 0)
		nc++;
	col_print_loopf(cw, nc, count, array);
}
