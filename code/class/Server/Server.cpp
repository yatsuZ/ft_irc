/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:23:05 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/27 16:57:13 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

//////////////////////////////////////////////////////////// Methode pour defnir les attribut individuellement

/// @brief verifier que argv1 est un port legit et return sa valeur en uint16_t  sinon envoie une exception, un bon port est compris entre 1 et 65535
/// @param argv1 Le premier arguement qui est un port en string
/// @return uint16_t le port par argv1
uint16_t  Server::_is_a_legit_port(std::string & argv1)
{
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

/// @brief Initialise la FD socket
/// @return le fd
int Server::_init_socket()
{
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd < 0)
		_throw_except("Erreur lors de la création du socket");
	return (socketfd);
}

//////////////////////////////////////////////////////////// Methode de Parametrage

/// @brief Configure le port et les sockets
void Server::_bind_and_listen()
{
	const sockaddr *sock_addr_serv_in_ptr = reinterpret_cast<const sockaddr *>(&this->_sock_addr_serv_in);

	// Configure l'option SO_REUSEADDR 
	int opt = REUSEADDR_OPTION;
	// Sa permet de dire que le port peut etre desactiver rapidement et reutiliser
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		_throw_except("Erreur lors de la configuration de SO_REUSEADDR.");

	// Configure la socket en mode non-bloquant
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) < 0)
		_throw_except("Erreur lors de la mise en mode non-bloquant de la socket.");

	// Associe la socket fd a la structure de sockaddr_in
	if (bind(this->_socketfd, sock_addr_serv_in_ptr, sizeof(this->_sock_addr_serv_in)) < 0)
		_throw_except("Erreur lors de l'association de l'adresse à la socket.");
	// std::cout << "Adresse associée à la socket avec succès." << std::endl;

	// Dis au fd decouter lentre du port
	if (listen(this->_socketfd, SOMAXCONN) < 0)
		_throw_except("Erreur lors de la mise en écoute de la socket.");
	// std::cout << "Socket en écoute sur le port " << this->get_port() << "." << std::endl;
}

void	Server::_paramPoll(void)
{
	// Structure pour poll
	struct pollfd server_pollfd;

	server_pollfd.fd = _socketfd;	// La socket du serveur
	server_pollfd.events = POLLIN;	// On surveille les événements de lecture (connexion entrante)
	server_pollfd.revents = 0;
	_all_pollfd.push_back(server_pollfd);
}


//////////////////////////////////////////////////////////// Constructeur Destructeur de la class

Server::Server():
_name("Nom_du_Serveur"),
_port(-1),
_mot_de_passe(""),
_socketfd(-1)
{
	// std::cout << BLUE << "Constructeur de Server" << std::endl;
}

/// @brief Constructeur du serveur
/// @param argv1 Le port qui sera parser et configurer en temp que _port
/// @param argv2 Le mot de passe du serveur qui sera stockée dans _mdp
Server::Server(std::string &argv1, std::string &argv2):
_name(SERVER_NAME),
_port(this->_is_a_legit_port(argv1)),
_mot_de_passe(this->_is_a_legit_mdp(argv2)),
_socketfd(this->_init_socket())
{
	// std::cout << BLUE << "Constructeur de Server" << NOCOLOR << std::endl;
	this->_sock_addr_serv_in.sin_family = AF_INET;
	this->_sock_addr_serv_in.sin_addr.s_addr = inet_addr(ADDRESSE_IP_IN);
	this->_sock_addr_serv_in.sin_port = htons(this->get_port());      // Port en format réseau (big-endian)

	this->_bind_and_listen();
	
	this->_paramPoll();
	
	std::cout << GREEN << "Construction de Server Fini" << NOCOLOR << std::endl;
}

Server::~Server()
{
	std::cout << RED << "Destructeur de Server" << NOCOLOR << std::endl;
	for (std::vector<struct pollfd>::iterator i = this->_all_pollfd.begin(); i != this->_all_pollfd.end(); i++)
	{
		if ((*i).fd > 0)
			close((*i).fd);
	}
}

//////////////////////////////////////////////////////////// Autre Methode Utile

/// @brief Envoie une exception de type Init_serv_error et ferme correctemen le serveru (car sa ne passera pas automatiquemetn pas le destructeur)
/// @param msg le message de lexception
void Server::_throw_except(const std::string &msg)
{
	if (_socketfd != -1)
		close(_socketfd);
	throw Init_serv_error(msg);
}