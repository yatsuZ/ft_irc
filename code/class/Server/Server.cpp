/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:23:05 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/16 03:41:55 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

/// @brief verifier que argv1 est un port legit et return sa valeur en uint16_t  sinon envoie une exception, un bon port est compris entre 1 et 65535
/// @param argv1 Le premier arguement qui est un port en string
/// @return uint16_t le port par argv1
uint16_t  Server::_is_a_legit_port(std::string & argv1)
{
	for (size_t i = 0; i < argv1.size(); ++i) {
		if (!std::isdigit(argv1[i])) {
			throw Init_serv_error("Le premier argument : \"" + argv1 + "\" n'est pas un nombre valide.");
		}
	}

	bool error = false;
	long portl = ft_atol_limits(argv1, 1, 65535, &error);
	uint16_t port;

	// Vérifie si la conversion a échoué ou si le port n'est pas dans la plage 1-65535
	if (error)
		throw Init_serv_error("Le premier argument : \"" + argv1 + "\" n'est pas un port valide (doit être entre 1 et 65535).");

	// Cast du long vers uint16_t après avoir vérifié que la valeur est dans la plage
	port = static_cast<uint16_t>(portl);

	return port;
}


/// @brief Verifie que le 2iem argument est un bon mot de passe, un bon mot de passe doit etre composée que de caractere alphanumerique sans separateur
/// @param argv2 Le 2iem argument qui est sensé etre le mot de passe
/// @return le mot de passe
std::string Server::_is_a_legit_mdp(std::string & argv2) {
	for (size_t i = 0; i < argv2.size(); ++i) {
		if (!std::isalnum(argv2[i]))
			throw Init_serv_error("Le Deuxième argument : \"" + argv2 + "\" n'est pas un mot de passe valide (doit être composé uniquement de caractères alphanumériques).");
	}

	return std::string(argv2);
}

int Server::_init_socket()
{
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
			throw Init_serv_error("Erreur lors de la création du socket");
	return (socketfd);
}


//////////////////

Server::Server():
_name("Nom du Serveur"),
_port(-1),
_mot_de_passe(""),
_socketfd(-1)
{
	std::cout << getColorCode(BLUE) << "Constructeur de Server" << std::endl;
}

Server::Server(std::string argv1, std::string argv2):
_name("Nom du Serveur"),
_port(this->_is_a_legit_port(argv1)),
_mot_de_passe(this->_is_a_legit_mdp(argv2)),
_socketfd(this->_init_socket())
{
	std::cout << getColorCode(BLUE) << "Constructeur de Server" << getColorCode(NOCOLOR) << std::endl;
	this->_sock_addr_serv_in.sin_family = AF_INET;
	this->_sock_addr_serv_in.sin_addr.s_addr = inet_addr(ADDRESSE_IP_IN);
	this->_sock_addr_serv_in.sin_port = htons(this->get_port());      // Port en format réseau (big-endian)
}

Server::~Server()
{
	std::cout << getColorCode(RED) << "DEstructeur de Server" << getColorCode(NOCOLOR) << std::endl;
	if (this->_socketfd > -1)
		close(this->_socketfd);
}

std::ostream	&operator<<( std::ostream & o, Server const & serv)
{
	sockaddr_in const &socket_adresse_in = serv.get_socke_addr_serv();
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &socket_adresse_in.sin_addr, ip_str, INET_ADDRSTRLEN);
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	o << "Voici Toutes les information du server" << std::endl;
	o << getColorCode(YELLOW) << "Le nom du Serveur = " << getColorCode(BLUE) << serv.get_name() << getColorCode(NOCOLOR) << std::endl;
	o << getColorCode(YELLOW) << "Le mot de passe du Serveur = " << getColorCode(BLUE) << serv.get_mdp() << getColorCode(NOCOLOR) << std::endl;
	o << getColorCode(YELLOW) << "Le file descriptor du socket = " << getColorCode(BLUE) << serv.get_socketfd() << getColorCode(NOCOLOR) << std::endl;
	o << getColorCode(YELLOW) << "Socket IN Adresse IP du serveur = " << getColorCode(BLUE) << getColorCode(NOCOLOR) << ip_str << std::endl;
	o << getColorCode(YELLOW) << "Le port du Serveur = " << getColorCode(BLUE) << serv.get_port() << getColorCode(NOCOLOR) << std::endl;
	o << getColorCode(YELLOW) << "Le port du Serveur a parti de socket adresse in = " << getColorCode(BLUE) << ntohs(socket_adresse_in.sin_port) << getColorCode(NOCOLOR) << std::endl;
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	return o;
}