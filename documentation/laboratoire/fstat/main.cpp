/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/28 14:45:41 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

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
	int fd = open("info.md", O_RDONLY);
	if (fd == -1) {
		std::cerr << RED << "Erreur: Impossible d'ouvrir le fichier. " << strerror(errno) << NOCOLOR << std::endl;
		return 1;
	}

	struct stat fileStat;
	if (fstat(fd, &fileStat) == -1) {
		std::cerr << RED << "Erreur: Impossible d'obtenir les informations du fichier. " << strerror(errno) << NOCOLOR << std::endl;
		close(fd);
		return 1;
	}

	std::cout << GREEN << "Informations du fichier:" << NOCOLOR << std::endl;
	std::cout << YELLOW << "Identifiant de périphérique contenant le fichier: " << BLUE << fileStat.st_dev << NOCOLOR << std::endl;
	std::cout << YELLOW << "Numéro d'inœud: " << BLUE << fileStat.st_ino << NOCOLOR << std::endl;
	std::cout << YELLOW << "Mode de protection (et type de fichier): " << BLUE << fileStat.st_mode << NOCOLOR << std::endl;
	std::cout << YELLOW << "Nombre de liens matériels: " << BLUE << fileStat.st_nlink << NOCOLOR << std::endl;
	std::cout << YELLOW << "UID du propriétaire: " << BLUE << fileStat.st_uid << NOCOLOR << std::endl;
	std::cout << YELLOW << "GID du propriétaire: " << BLUE << fileStat.st_gid << NOCOLOR << std::endl;
	std::cout << YELLOW << "Identifiant de périphérique (si c'est un périphérique spécial): " << BLUE << fileStat.st_rdev << NOCOLOR << std::endl;
	std::cout << YELLOW << "Taille totale en octets: " << BLUE << fileStat.st_size << NOCOLOR << std::endl;
	std::cout << YELLOW << "Taille de bloc pour E/S du système de fichiers: " << BLUE << fileStat.st_blksize << NOCOLOR << std::endl;
	std::cout << YELLOW << "Nombre de blocs alloués: " << BLUE << fileStat.st_blocks << NOCOLOR << std::endl;
	std::cout << YELLOW << "Heure du dernier accès: " << CYAN << ctime(&fileStat.st_atime) << NOCOLOR;
	std::cout << YELLOW << "Heure de la dernière modification: " << CYAN << ctime(&fileStat.st_mtime) << NOCOLOR;
	std::cout << YELLOW << "Heure du dernier changement d'état: " << CYAN << ctime(&fileStat.st_ctime) << NOCOLOR;

	// Fermer le fichier
	close(fd);

	return 0;
}
