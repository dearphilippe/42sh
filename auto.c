/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:53:35 by passef            #+#    #+#             */
/*   Updated: 2018/04/14 20:48:16 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <minishell.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct	s_autoNode
{
		struct	s_autoNode *child[26];
		int		isLeaf;
}				t_autoNode;

t_autoNode	*initNode(void)
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

void		insert_node(t_autoNode *root, char *word)
{
	int		lvl;
	int		len;
	int		i;

	len = ft_strlen(word);
	lvl = 0;

	t_autoNode	*pCrawl;
	pCrawl = root;

	while (lvl < len)
	{
		i = (int)word[lvl] - (int)'a';
		lvl++;
	}
}

void		build_trie(t_shell *sh)
{
	int i;
	struct autoNode *root;

	root = initNode();

	i = 0;

	char keys[][8] = {"the", "a", "there", "answer", "any",
				"by", "bye", "their"};

	while (i < ft_strlen(keys))
	{
		insert(root, keys[i]);
		i++;
	}
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

int			main(int ac, char const * const *av)
{
	
	return (0);
}

	//sh->buf_i position actuel du curseur

	/*
	** il faut que lorsque l'utilisateur commence a taper je cherches la premiere fois qu'il tape tab,
	** s'il tape tab pour la premiere fois avant de taper espace alors je lui suggere la liste des commandes
	** sinon je suggere à l'utilisateur la liste des fichiers.
	** Si l'utilisateur a taper une operations comme |, &&, ;, || alors je recommences.
	*/
/*
int		str_has_op(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (IS_RED_AC(str[i]))
			return (0);
		i++;
	}

	return (1);
}
*/

/*
** si le dernier mot est cd 
** 
*/