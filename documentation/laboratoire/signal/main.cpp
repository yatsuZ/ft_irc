/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 01:33:02 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <cstdlib>

// Gestionnaire pour SIGINT (Ctrl+C)
void handle_sigint(int signum) {
	(void) signum;
	std::cout << std::endl << "Signal SIGINT reçu. Terminaison propre." << std::endl;
	exit(0); // Quitter proprement
}

// Gestionnaire pour SIGTERM
void handle_sigterm(int signum) {
	(void) signum;
	std::cout << "Signal SIGTERM reçu. Terminaison propre." << std::endl;
	exit(0); // Quitter proprement
}

int main() {
	// Installer les gestionnaires de signaux
	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_sigterm);

	std::cout << "Programme en cours d'exécution. Appuyez sur Ctrl+C ou envoyez SIGTERM pour terminer." << std::endl;

	// Boucle infinie pour maintenir le programme en cours d'exécution
	while (true) {
		sleep(1);
	}

	return 0;
}