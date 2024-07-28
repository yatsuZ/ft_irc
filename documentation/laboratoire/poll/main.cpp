/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/18 14:44:52 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>		// pour EXIT_SUCCESS, EXIT_FAILURE

int main() {
	struct pollfd fds[3];
	int timeout_msecs = 5000; // 5 secondes
	int ret;

	// Surveiller stdin (fd 0) pour la lecture
	fds[0].fd = 0; // stdin
	fds[0].events = POLLIN; // Surveiller les événements de lecture

	// Surveiller stdout (fd 1) pour l'écriture
	fds[1].fd = 1; // stdout
	fds[1].events = POLLOUT; // Surveiller les événements d'écriture

	// Créer une pipe pour générer une condition d'exception
	int pipefds[2];
	if (pipe(pipefds) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// Fermer l'extrémité de lecture pour provoquer une erreur sur l'écriture
	close(pipefds[0]);

	fds[2].fd = pipefds[1]; // Extrémité d'écriture de la pipe
	fds[2].events = POLLOUT | POLLERR | POLLHUP; // Surveiller les événements d'écriture, d'erreur et de déconnexion

	// Appel à poll
	ret = poll(fds, 3, timeout_msecs);

	if (ret == -1) {
		perror("poll");
	} else if (ret == 0) {
		std::cout << "Aucun descripteur prêt dans les 5 secondes" << std::endl;
	} else {
		// Vérifier si stdin est prêt pour la lecture
		if (fds[0].revents & POLLIN)
			std::cout << "stdin est prêt pour la lecture" << std::endl;

		// Vérifier si stdout est prêt pour l'écriture
		if (fds[1].revents & POLLOUT)
			std::cout << "stdout est prêt pour l'écriture" << std::endl;

		// Vérifier si l'extrémité d'écriture de la pipe a une condition d'erreur ou de déconnexion
		if (fds[2].revents & POLLERR)
			std::cout << "Erreur sur l'extrémité d'écriture de la pipe" << std::endl;

		if (fds[2].revents & POLLHUP)
			std::cout << "Déconnexion sur l'extrémité d'écriture de la pipe" << std::endl;

		if (fds[2].revents & POLLNVAL)
			std::cout << "Descripteur de fichier non valide sur l'extrémité d'écriture de la pipe" << std::endl;
	}

	// Fermer l'extrémité d'écriture de la pipe
	close(pipefds[1]);

	return 0;
}
