/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:53:35 by passef            #+#    #+#             */
/*   Updated: 2018/04/15 12:23:10 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "minishell.h"

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

typedef struct	s_autoNode
{
		struct	s_autoNode *child[128];
		int		isLeaf;
}				t_autoNode;

t_autoNode		*initNode(void)
{
	t_autoNode *node;

	node = NULL;
	node = (t_autoNode *)malloc(sizeof(t_autoNode));
	if (node)
	{
		int i;

		node->isLeaf = 0;
		while (i < 26)
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
		printf("i : %d\n lvl : %d\n len : %d\n", i, lvl, len);
		printf("word[lvl] : %c\n ", word[lvl]);
		i = (int)word[lvl];
		printf("%d\n", i);
		printf("%s\n", nCrawl->child[i][i]);
		if (!nCrawl->child[i])
			nCrawl->child[i] = initNode();
		nCrawl = nCrawl->child[i];
		lvl++;
	}

	nCrawl->isLeaf = 1;
}

t_autoNode		*build_trie(char **tab)
{
	int i;
	t_autoNode *root;

	root = initNode();
	i = 0;

	while (i < ARRAY_SIZE(tab))
	{
		insert_node(root, tab[i]);
		i++;
	}
	return (root);
}

int				search(t_autoNode *root, const char *word)
{
	int lvl;
	int len;
	int i;
	t_autoNode *pCrawl;

	len = ft_strlen(word);
	lvl = 0;
	pCrawl = root;

	while (lvl < len)
	{
		i = (int)word[lvl];
		if (!pCrawl->child[i])
			return (0);
		pCrawl = pCrawl->child[i];
		lvl++;
	}

	return (pCrawl != NULL && pCrawl->isLeaf);
}

int				main(int argc, char **argv, char **envp)
{
	t_autoNode *root;

	root = initNode();

	insert_node(root, "philippe");
	/*
	char **keys;

	keys = malloc(sizeof(keys) * 8);

	keys[0] = "the";
	keys[1] = "a";
	keys[2] = "there";
	keys[3] = "answer";
	keys[4] = "any";
	keys[5] = "by";
	keys[6] = "bye";
	keys[7] = "their";
	keys[8] = NULL;

	char output[][32] = {"Not in the team", "Present is a number 10"};

	root = build_trie(keys);
	printf("%s --- %s\n", "the", output[search(root, "the")] );
	printf("%s --- %s\n", "there", output[search(root, "there")] );
	printf("%s --- %s\n", "thei", output[search(root, "thei")] );
	printf("%s --- %s\n", "thaw", output[search(root, "thaw")] );
	*/
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