/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:53:35 by passef            #+#    #+#             */
/*   Updated: 2018/04/15 17:40:44 by passef           ###   ########.fr       */
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

int				main(int argc, char **argv, char **envp)
{
	t_autoNode *root;

	root = initNode();
	char **keys;
	keys = malloc(sizeof(keys) * 6);

	keys[0] = "Phil";
	keys[1] = "alëx";
	keys[2] = "Bac$ir";
	keys[3] = "=ei4";
	keys[4] = "L	eo";
	keys[5] = "p-f";
	keys[6] = NULL;
	
	root = build_trie(keys);
	char output[][32] = {"Not in the team", "Present is the place"};
	printf("%s --- %s\n", "Bac$ir", output[search(root, "Bac$ir")] );
	printf("%s --- %s\n", "L	eo", output[search(root, "L	eo")] );
	printf("%s --- %s\n", "p-f", output[search(root, "p-f")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );

	return (0);
}

/*
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