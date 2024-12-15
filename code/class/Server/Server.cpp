/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:23:05 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/16 00:26:07 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

/// @brief verifier que argv1 est un port legit et return sa valeur en unsigned long sinon envoie une exception, un bon port est compris entre 1 et 65535
/// @param argv1 Le premier arguement qui est un port en string
/// @return unsigned long le port par argv1
unsigned long Server::_is_a_legit_port(std::string & argv1)
{
	for (size_t i = 0; i < argv1.size(); ++i) {
		if (!std::isdigit(argv1[i])) {
			throw Init_serv_error("Le premier argument : \"" + argv1 + "\" n'est pas un nombre valide.");
		}
	}

	unsigned long port;
	std::istringstream iss(argv1);
	iss >> port;

	// Vérifie si la conversion a échoué ou si le port n'est pas dans la plage 1-65535
	if (iss.fail() || port < 1 || port > 65535)
		throw Init_serv_error("Le premier argument : \"" + argv1 + "\" n'est pas un port valide (doit être entre 1 et 65535).");

	return port;
}


/// @brief Verifie que le 2iem argument est un bon mot de passe, un bon mot de passe doit etre composée que de caractere alphanumerique sans separateur
/// @param argv2 Le 2iem argument qui est sensé etre le mot de passe
/// @return le mot de passe
std::string Server::_is_a_legit_mdp(std::string & argv2) {
	for (size_t i = 0; i < argv2.size(); ++i) {
		if (!std::isalnum(argv2[i])) {
			throw Init_serv_error("Le Deuxième argument : \"" + argv2 + "\" n'est pas un mot de passe valide (doit être composé uniquement de caractères alphanumériques).");
		}
	}

	return std::string(argv2);
}


//////////////////

Server::Server(): _name("Nom du Serveur"), _port(0), _mot_de_passe("")
{
	std::cout << getColorCode(BLUE) << "Constructeur de Server" << std::endl;
	std::cout << getColorCode(GREEN) << "Server->_name = " << getColorCode(YELLOW) << _name << getColorCode(NOCOLOR) << std::endl;
}

Server::Server(std::string argv1, std::string argv2): _name("Nom du Serveur"), _port(this->_is_a_legit_port(argv1)), _mot_de_passe(this->_is_a_legit_mdp(argv2))
{
	std::cout << getColorCode(BLUE) << "Constructeur de Server" << getColorCode(NOCOLOR) << std::endl;
	std::cout << *this;
}

Server::~Server()
{
	std::cout << getColorCode(RED) << "DEstructeur de Server" << getColorCode(NOCOLOR) << std::endl;
}

std::ostream	&operator<<( std::ostream & o, Server const & serv)
{
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	o << "Voici Toutes les information du server" << std::endl;
	o << getColorCode(YELLOW) << "Le nom du Serveur = " << getColorCode(BLUE) << serv.get_name() << getColorCode(NOCOLOR) << std::endl;
	o << getColorCode(YELLOW) << "Le port du Serveur = " << getColorCode(BLUE) << serv.get_port() << getColorCode(NOCOLOR) << std::endl;
	o << getColorCode(YELLOW) << "Le mot de passe du Serveur = " << getColorCode(BLUE) << serv.get_mdp() << getColorCode(NOCOLOR) << std::endl;
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	return o;
}