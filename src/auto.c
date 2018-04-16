/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:53:35 by passef            #+#    #+#             */
/*   Updated: 2018/04/15 20:54:34 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "minishell.h"

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

	return;
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


int	directory_count_entries(char *path)
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


char **directory_get_contents(char *path)
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

void	directory_print_contents(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf(STDOUT_FILENO, "index = %d, entry = %s\n", i, array[i]);
		i++;
	}
	return ;
}

void			auto_complete(t_shell *sh)
{
	ft_printf(STDIN_FILENO, "ca marche\n");

	return ;
}
