/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/28 14:24:05 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <csignal>
#include <cstring>
#include <unistd.h>  // pour sleep

// Définir les couleurs
#define NOCOLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define PURPLE "\033[35m"

int interrupt_count = 0;

void signal_handler(int signal_num) {
	++interrupt_count;
	std::cout << RED << "Signal reçu: " << signal_num << " (" << interrupt_count << "/3)" << NOCOLOR << std::endl;
	
	if (interrupt_count >= 3) {
		std::cout << GREEN << "Restoration du comportement par défaut pour SIGINT." << NOCOLOR << std::endl;
		
		// Restaurer le comportement par défaut de SIGINT
		struct sigaction sa;
		std::memset(&sa, 0, sizeof(sa));
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
	}
}

int main()
{
	int	second = 15;
	struct sigaction sa;

	// Initialiser la structure sigaction à zéro
	std::memset(&sa, 0, sizeof(sa));

	// Spécifier le gestionnaire de signal
	sa.sa_handler = signal_handler;

	// Spécifier les signaux à intercepter
	if (sigaction(SIGINT, &sa, NULL) != 0) {
		std::cerr << RED << "Erreur: Impossible d'intercepter SIGINT." << NOCOLOR << std::endl;
		return 1;
	}

	std::cout << GREEN << "Appuyez sur Ctrl+C pour envoyer SIGINT (3 interruptions pour restaurer le comportement par défaut)" << NOCOLOR << std::endl;

	// Boucle avec pause pour permettre la réception de signaux
	for (int i = 0; i < second; ++i) {
		std::cout << YELLOW << "Attente... " << (second - i) << " secondes restantes." << NOCOLOR << std::endl;
		sleep(1);
	}

	std::cout << GREEN << "Programme terminé sans interruption." << NOCOLOR << std::endl;

	return 0;
}
