/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_keys_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:16:43 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/08 21:10:12 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft.h"

const char	*g_special_keys[] = {KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW,
	KEY_RIGHT_ARROW, KEY_BACKSPACE, KEY_DELETE, KEY_CTRL_A, KEY_CTRL_E,
	KEY_CTRL_K, KEY_CTRL_L, KEY_TAB, KEY_SHIFT_LEFT, KEY_SHIFT_RIGHT,
	KEY_CTRL_U, KEY_CTRL_P};

void	key_shift_left(t_shell *sh)
{
	int	i;

	i = sh->buf_i;
	if (&sh->buffer[i] > sh->buffer)
		i--;
	while ((&sh->buffer[i] > sh->buffer) && (sh->buffer[i] == ' ')
			&& (sh->buffer[i - 1] != '\n'))
		i--;
	while ((&sh->buffer[i] > sh->buffer) && (sh->buffer[i - 1] != ' ')
			&& (sh->buffer[i - 1] != '\n'))
		i--;
	sh->buf_i = i;
	reprint_input(sh);
}

void	key_shift_right(t_shell *sh)
{
	int	i;
	int	k;

	i = sh->buf_i;
	k = sh->input_size;
	if (&sh->buffer[i] < &sh->buffer[k])
		i++;
	while ((&sh->buffer[i] < &sh->buffer[k]) && (sh->buffer[i] != ' '))
		i++;
	while ((&sh->buffer[i] < &sh->buffer[k]) && (sh->buffer[i] == ' '))
		i++;
	sh->buf_i = i;
	reprint_input(sh);
}

void	key_ctrl_u_function(t_shell *sh)
{
	int i;

	if (sh->clipboard != NULL)
		free(sh->clipboard);
	i = sh->input_size;
	while ((&sh->buffer[i] > sh->buffer) && (sh->buffer[i - 1] != '\n'))
		i--;
	sh->clipboard = ft_strdup(&sh->buffer[i]);
	sh->buf_i = i;
	sh->input_size = sh->buf_i;
	ft_bzero(&sh->buffer[sh->buf_i], sh->bufsize - sh->buf_i);
	ft_putstr(sh->clear_till_eol);
	reprint_input(sh);
	return ;
}

void	key_ctrl_p_function(t_shell *sh)
{
	int	i;
	int	k;

	if (sh->clipboard == NULL)
		return ;
	k = ft_strlen(sh->clipboard);
	i = 0;
	while (i < k)
	{
		(void)insert_character(&sh->buffer[sh->buf_i], sh->clipboard[i]);
		i++;
		sh->buf_i++;
		sh->input_size++;
	}
	reprint_input(sh);
	return ;
}

void	check_special_keys(t_shell *sh)
{
	int			i;
	const char	*key;
	int			len;
	static void	(*special_key_functions[]) (t_shell *) = {
	&key_up_arrow_function, &key_down_arrow_function, &key_left_arrow_function,
	&key_right_arrow_function, &key_backspace_function, &key_delete_function,
	&key_ctrl_a_function, &key_ctrl_e_function, &key_ctrl_k_function,
	&key_ctrl_l_function, &key_tab_function, &key_shift_left, &key_shift_right,
	&key_ctrl_u_function, &key_ctrl_p_function};

	i = 0;
	while (i < NUM_SPECIAL_KEYS)
	{
		key = g_special_keys[i];
		len = ft_strlen(key);
		if (ft_strncmp(key, sh->keycode, len) == 0)
		{
			(void)ft_bzero(sh->keycode, 9);
			return (special_key_functions[i](sh));
		}
		i++;
	}
	return ;
}
