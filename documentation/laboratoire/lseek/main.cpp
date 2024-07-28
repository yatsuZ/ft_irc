/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/28 14:38:14 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fcntl.h>   // pour open
#include <unistd.h>  // pour lseek, read, close
#include <cerrno>    // pour errno
#include <cstring>   // pour strerror

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

int main() {
	// Ouvrir un fichier en lecture seule
	int fd = open("main.cpp", O_RDONLY);
	if (fd == -1) {
		std::cerr << RED << "Erreur: Impossible d'ouvrir le fichier. " << strerror(errno) << NOCOLOR << std::endl;
		return 1;
	}

	// Déplacer le pointeur de fichier à 10 octets depuis le début
	off_t new_pos = lseek(fd, 10, SEEK_SET);
	if (new_pos == (off_t)-1) {
		std::cerr << RED << "Erreur: Impossible de déplacer le pointeur de fichier. " << strerror(errno) << NOCOLOR << std::endl;
		close(fd);
		return 1;
	}

	std::cout << GREEN << "Le pointeur de fichier a été déplacé à la position " << new_pos << NOCOLOR << std::endl;

	// Lire et afficher le contenu du fichier à partir de la nouvelle position
	char buffer[128];
	ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1) {
		std::cerr << RED << "Erreur: Impossible de lire le fichier. " << strerror(errno) << NOCOLOR << std::endl;
		close(fd);
		return 1;
	}

	buffer[bytes_read] = '\0';  // Assurer que le buffer est terminé par un nul
	std::cout << YELLOW << "Contenu lu: " << buffer << NOCOLOR << std::endl;

	// Fermer le fichier
	close(fd);

	return 0;
}
