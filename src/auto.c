/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:53:35 by passef            #+#    #+#             */
/*   Updated: 2018/04/18 02:30:47 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "ft.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define CHILD_SIZE 128

typedef struct	s_autoNode
{
		struct	s_autoNode *child[CHILD_SIZE];
		int		isLeaf;
}				t_autoNode;

t_autoNode		*initNode(void)
{
	t_autoNode *node;
	int i;

	i = 0;

	node = NULL;
	node = (t_autoNode *)malloc(sizeof(t_autoNode));
	if (node)
	{
		node->isLeaf = 0;
		while (i < CHILD_SIZE)
		{
			node->child[i] = NULL;
			i++;
		}
	}

	return (node);
}

void			insert_node(t_autoNode *root, char *word)
{
	int		lvl;
	int		len;
	int		i;

	len = ft_strlen(word);
	lvl = 0;
	i = 0;

	t_autoNode	*nCrawl;
	nCrawl = root;

	while (lvl < len)
	{
		// printf("mot : %s\n lvl : %d\n lettre : %c\n", word, lvl, word[lvl]);
		i = (int)word[lvl];
		if (!nCrawl->child[i])
			nCrawl->child[i] = initNode();
		nCrawl = nCrawl->child[i];
		lvl++;
	}

	nCrawl->isLeaf = 1;
}

int				search(t_autoNode *root, const char *word)
{
	int lvl;
	int len;
	int i;
	t_autoNode *nCrawl;

	len = ft_strlen(word);
	lvl = 0;
	i = 0;
	nCrawl = root;

	while (lvl < len)
	{
		i = (int)word[lvl];
		if (!nCrawl->child[i])
			return (0);
		nCrawl = nCrawl->child[i];
		lvl++;
	}

	return (nCrawl != NULL && nCrawl->isLeaf);
}

t_autoNode		*build_trie(char **tab)
{
	int i;
	t_autoNode *root;

	root = initNode();
	i = 0;

	while (i < count_char_array(tab))
	{
		insert_node(root, tab[i]);
		i++;
	}
	return (root);
}


int				directory_count_entries(char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	if (path == NULL)
		return (-1);
	if ((dirp = opendir(path)) == NULL)
	{
		perror("autocomplete");
		return (-1);
	}
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		i++;
	closedir(dirp);
	return (i);
}


char			**directory_get_contents(char *path)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;
	char			**vector;

	if ((i = directory_count_entries(path)) == -1)
		return (NULL);
	vector = ft_memalloc((i + 1) * sizeof(char *));
	if (path == NULL)
		return (NULL);
	if ((dirp = opendir(path)) == NULL)
	{
		perror("autocomplete");
		return (NULL);
	}
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
		vector[i++] = ft_strdup(dp->d_name);
	vector[i] = NULL;
	closedir(dirp);
	return (vector);
}

void			directory_print_contents(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf(STDOUT_FILENO, "%s\n", array[i]);
		i++;
	}
	return ;
}

int		count_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		i++;	

	return (i);	
}

char	**cpy_array(char **arr)
{
	int i;
	char **tmp;

	
	
	i = 0;
	while (arr[i])
	{
		
	}
}

int		tab_max_len(char **array)
{
	int		i;
	int		len;
	int		max_len;

	i = 0;
	max_len = 0;
	while (array[i] != NULL)
	{
		len = ft_strlen(array[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

void	tab_print_colum(char **array, int count)
{
	int				max_len;
	int				cw;
	struct winsize	ws;
	int				nc;

	ft_printf(STDOUT_FILENO, "\n");
	max_len = tab_max_len(array);
	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		return ;
	cw = max_len + 2;
	nc = ws.ws_col / cw;
	col_print_loop(cw, nc, count, array);
}

void	auto_complete(t_shell *sh)
{
	char		**dir;
	t_autoNode	*root;
	int			i;
	int			c;

	root = initNode();
	i = 0;
	if ((dir = directory_get_contents(".")) != NULL)
	{
		while (dir[i] != NULL)
		{
			add_to_list_of_executables(sh, dir[i]);
			i++;
		}
		c = count_array(dir);
		// directory_print_contents(dir);
		root = build_trie(dir);
		tab_print_col(dir, c);
		// if (search(root, "parse"))
			// reprint_input(sh);
		destroy_char_array(dir);
	}

	sh->buf_i = 0;
	return ;
}

/* 

---------- print colums --------------

Print output colum : tab_print_columns(matches, i);
Print prompt : reprint_input(sh);
void	add_to_list_of_executables(t_shell *sh, char *cmd)
void	destroy_list_of_executables(t_shell *sh);

*/

/*

int				main(int argc, char **argv, char **envp)
{
	t_autoNode *root;
	char **keys;
	char **dir;


	root = initNode();
	keys = malloc(sizeof(keys) * 6);

	keys[0] = "Phil";
	keys[1] = "alëx";
	keys[2] = "Bac$ir";
	keys[3] = "=ei4";
	keys[4] = "L	eo";
	keys[5] = "p-f";
	keys[6] = NULL;
	

	if ((dir = directory_get_contents(".")) != NULL)
	{
		directory_print_contents(dir);
		destroy_char_array(dir);
	}
	


	root = build_trie(keys);
	char output[][32] = {"Not in the team", "Present is the place"};
	printf("%s --- %s\n", "Bac$ir", output[search(root, "Bac$ir")] );
	printf("%s --- %s\n", "L	eo", output[search(root, "L	eo")] );
	printf("%s --- %s\n", "p-f", output[search(root, "p-f")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );

	return (0);
}

void		display_complete(t_shell *sh)
{
	DIR	*cDir;
	struct dirent *dp;
	char	name;

	if (cDir = opendir("."))
	{
		return (EXIT_FAILURE);
	}
	name = "Documents";

	while (cDir)
	{
		if ((dp = readdir(cDir)) != NULL)
		{
			if (ft_strcmp(dp->d_name, name) == 0)
			{
				closedir(cDir);
				return (0);
			}
		}
	}
}
*/