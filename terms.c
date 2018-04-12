/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 21:24:38 by passef            #+#    #+#             */
/*   Updated: 2018/04/06 10:30:28 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <term.h>
#include <stdbool.h>

#include "shell.h"

#define TRUE 1
#define FALSE 0

#define MAX_KEY_STRING_LENGTH 4096

#define KEY_CODE_NONE 0
#define KEY_CODE_OTHER 0
#define KEY_CODE_CTRL_D 0
#define KEY_CODE_CTRL_R 0
#define KEY_CODE_TAB 0
#define KEY_CODE_HOME 0
#define KEY_CODE_END 0
#define KEY_CODE_PUP 0
#define KEY_CODE_PDOWN 0
#define KEY_CODE_UP 0
#define KEY_CODE_DOWN 0
#define KEY_CODE_LEFT 0
#define KEY_CODE_RIGHT 0
#define KEY_CODE_RET 0
#define KEY_CODE_MAX 0

/*

typedef struct		key_type_t
{
	int		value[10];
	char	*type;
}					key_type_t;

static	struct		key_t
{
	key_type_t		k;
	char const		*s;
};

*/

typedef struct	funcs_tab_s
{
	key_type_t	k;
	int			(*f)(char const * const);
}				funcs_tab_t;

int		key_is_ctrl_d(char const * const buff)
{
	char const * const ret = "\x4\0\0\0\0\0"; // equal to key_is_ctrl_d

	if (memcmp((void *) ret, (void *)buff, MAX_KEY_STRING_LENGTH) == 0)
		return TRUE;

	return FALSE;
}

int		key_is_ctrl_r(char const * const buff)
{
	char const * const ret = "\x12\0\0\0\0\0";

	if (memcmp((void *) ret, (void *)buff, MAX_KEY_STRING_LENGTH) == 0)
		return TRUE;

	return FALSE;
}

int		key_is_tab(char const * const buff)
{
	char const * const ret = "\x9\0\0\0\0\0";

	if (memcmp((void *) ret, (void *)buff, MAX_KEY_STRING_LENGTH) == 0)
		return TRUE;

	return FALSE;
}

int		key_is_down_arrow(char const * const buff)
{
	static char *arrow;

	arrow = NULL;

	if (arrow == NULL)
	{
		arrow = tgetstr("kd", NULL);
		arrow[1] = 91;
	}

	if (memcmp((void *) arrow, (void *) buff, strlen(arrow)) == 0)
		return TRUE;

	return FALSE;
}


int		key_is_left_arrow(char const * const buff)
{
	static char *arrow;

	arrow = NULL;

	if (arrow == NULL)
	{
		arrow = tgetstr("kl", NULL);
		arrow[1] = 91;
	}

	if (memcmp((void *) arrow, (void *) buff, strlen(arrow)) == 0)
		return TRUE;

	return FALSE;
}

int		key_is_right_arrow(char const * const buff)
{
	static char *arrow;

	arrow = NULL;

	if (arrow == NULL)
	{
		arrow = tgetstr("kr", NULL); // get the key press
		arrow[1] = 91;
	}

	if (memcmp((void *) arrow, (void *) buff, strlen(arrow)) == 0)
		return TRUE;

	return FALSE;
}

int		key_is_return(char const * const buff)
{
	char const * const ret = "\x0a\0\0\0\0\0";

	if (memcmp((void *) ret, (void *) buff, MAX_KEY_STRING_LENGTH) == 0)
		return TRUE;

	return FALSE;
}

static	key_t 		*key_new(key_type_t type, char const * const value)
{
	key_t	*new;

	new = NULL;

	new = (key_t *) malloc(sizeof(*new));
	new->type = type;
	(void) memcpy(new->value, value, MAX_KEY_STRING_LENGTH);

	return new;
}

void	key_dump (key_t const *key)
{
	char const *	s;
	unsigned int	i;

	s = NULL;
	i = 0;

	char const key_to_str[] =
	{
	{	KEY_CODE_NONE,		"KEY_CODE_NONE"		},
	{	KEY_CODE_OTHER,		"KEY_CODE_OTHER"	},
	{	KEY_CODE_CTRL_D,	"KEY_CODE_CTRL_D"	},
	{	KEY_CODE_CTRL_R,	"KEY_CODE_CTRL_R"	},
	{	KEY_CODE_TAB,		"KEY_CODE_TAB"		},
	{	KEY_CODE_HOME,		"KEY_CODE_HOME"		},
	{	KEY_CODE_END,		"KEY_CODE_END"		},
	{	KEY_CODE_PUP,		"KEY_CODE_PUP"		},
	{	KEY_CODE_PDOWN,		"KEY_CODE_PDOWN"	},
	{	KEY_CODE_UP,		"KEY_CODE_UP"		},
	{	KEY_CODE_DOWN,		"KEY_CODE_DOWN"		},
	{	KEY_CODE_LEFT,		"KEY_CODE_LEFT"		},
	{	KEY_CODE_RIGHT,		"KEY_CODE_RIGHT"	},
	{	KEY_CODE_RET,		"KEY_CODE_RET"		},
	{	KEY_CODE_MAX,		NULL				}
	};

	while (key_to_str[i].k != KEY_CODE_MAX)
	{
		if (key_to_str[i].k == key->type)
			s = key_to_str[i].s;
		i++;
	}

	printf("[%-9s][%x][%x][%x][%x][%x][%x]\r\n",
			s, ((int) key->value[0] ), ((int) key->value[1]),
			((int) key->value[2]), ((int) key->value[3]),
			((int) key->value[4]), ((int) key->value[5]));

	return ;
}

void	key_delete (key_t **akey)
{
	free( *akey );
	*akey = NULL;

	return ;
}

	/*
	** Check when we press a button if is the right one, it's help us to make a condition
	**
	*/
key_t	*key_get(char const * const buff)
{
	int i;

	i = 0;

	static	funcs_tab_t const	funcs[] =
	{
		{ KEY_CODE_CTRL_D, &key_is_ctrl_d },
		{ KEY_CODE_CTRL_R, &key_is_ctrl_r },
		{ KEY_CODE_TAB, &key_is_tab },
		// { KEY_CODE_HOME, &key_is_home },
		// { KEY_CODE_END, &key_is_end },
		// { KEY_CODE_PUP, &key_is_pup },
		// { KEY_CODE_PDOWN, &key_is_pdown },
		// { KEY_CODE_UP, &key_is_up_arrow },
		{ KEY_CODE_DOWN, &key_is_down_arrow },
		{ KEY_CODE_LEFT, &key_is_left_arrow },
		{ KEY_CODE_RIGHT, &key_is_right_arrow },
		{ KEY_CODE_RET, &key_is_return },
		{ KEY_CODE_NONE, NULL },
	};

	while (funcs[i].f != NULL) // Go through the tab and look for the right key
	{
		if ((funcs[i].f)(buff) == TRUE)
			return key_new (funcs[i].k, buff);
		i++;
	}

	return key_new(KEY_CODE_OTHER, buff);
}

/*
** Initialisation of termcaps
*/
void	raw_terminal_mode()
{
	struct	termios		tattr;

	tcgetattr( STDIN_FILENO, &tattr); // recuperation of termios attribute
	tattr.c_lflag &= ~( ECHO | ICANON ); // remove echo & canonique mode
	tattr.c_oflag &= ~( OPOST ); // remove OPOST mode
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr( STDIN_FILENO, TCSADRAIN, &tattr);
	tgetent(NULL, getenv("TERM")); // get env

	return ;
}

void	default_terminal_mode()
{
	struct	termios		tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= ( ECHO | ICANON );
	tattr.c_oflag |= ( OPOST );
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);

	return ;
}

/*
**
** Once termcaps is initialise, we make a while for similate a shell
** Set the buffer to 0
** Read on standard input
** Get everything with key_get function and dump it with key_dump
**
**/

int		main(void)
{
	char	buff[MAX_KEY_STRING_LENGTH];

	key_t	*key;
	int	stop;

	key = NULL;
	stop = FALSE;
	raw_terminal_mode();
	while (stop == FALSE)
	{
		(void) memset((void *) buff, 0, MAX_KEY_STRING_LENGTH);
		(void) read(STDIN_FILENO, buff, MAX_KEY_STRING_LENGTH);

		key = key_get(buff);
		key_dump( key );

		if ( key->type == KEY_CODE_CTRL_D )
			stop = TRUE;

		key_delete(&key);
	}

	default_terminal_mode();

	return (0);
}
