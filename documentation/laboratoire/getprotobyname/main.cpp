/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/27 00:56:13 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <netdb.h>  // Pour getprotobyname
#include <sys/socket.h>  // Pour socket
#include <cstring>  // Pour memset
#include <unistd.h>  // Pour close

int main() {
	// Nom du protocole que nous voulons rechercher
	const char* protocol_name = "tcp";

	// Obtenir les informations sur le protocole
	struct protoent* protocol_info = getprotobyname(protocol_name);
	if (protocol_info == NULL) {
		std::cerr << "Erreur : Protocole non trouvé" << std::endl;
		return 1;
	}

	// Afficher les informations sur le protocole
	std::cout << "Nom du protocole : " << protocol_info->p_name << std::endl;
	std::cout << "Numéro du protocole : " << protocol_info->p_proto << std::endl;

	// Créer une socket avec le protocole
	int sockfd = socket(AF_INET, SOCK_STREAM, protocol_info->p_proto);
	if (sockfd < 0) {
		std::cerr << "Erreur de création de la socket" << std::endl;
		return 1;
	}

	std::cout << "Socket créée avec succès" << std::endl;

	// Fermer la socket
	close(sockfd);
	return 0;
}