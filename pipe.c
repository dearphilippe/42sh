/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: passef <passef@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 12:45:30 by passef            #+#    #+#             */
/*   Updated: 2018/04/08 13:06:31 by passef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TAILLE_MESSAGE 256 /* Correspond à la taille de la chaîne à lire et à écrire */

int main(void)
{
	pid_t pid_fils;
	int fd_pipe[2];

	unsigned char messageLire[TAILLE_MESSAGE], messageEcrire[TAILLE_MESSAGE];

	printf("Création du tube.\n");
		
	if(pipe(fd_pipe) != 0)
	{
		fprintf(stderr, "Erreur de création du tube.\n");
		return EXIT_FAILURE;
	}

	pid_fils = fork();

	if(pid_fils == -1)	
	{
		fprintf(stderr, "Erreur de création du processus.\n");
		return 1;
	}

	if(pid_fils == 0)
	{
		printf("Fermeture de l'entrée dans le fils.\n\n");
		close(fd_pipe[1]);
		
		read(fd_pipe[0], messageLire, TAILLE_MESSAGE);
		printf("Nous sommes dans le fils (pid = %d).\nIl a reçu le message suivant du père : \"%s\".\n\n\n", getpid(), messageLire);
	}

	else
	{
		printf("\nFermeture de la sortie dans le père.\n");
		close(fd_pipe[0]);

		sprintf(messageEcrire, "Bonjour, fils. Je suis ton père !");

		printf("Nous sommes dans le père (pid = %d).\nIl envoie le message suivant au fils : \"%s\".\n\n\n", getpid(), messageEcrire);

		write(fd_pipe[1], messageEcrire, TAILLE_MESSAGE);

		wait(NULL);
	}

	return 0;
}
