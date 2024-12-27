/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:23:05 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/28 00:06:13 by yzaoui           ###   ########.fr       */
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
		_throw_except("Erreur lors de la création du socket");
	return (socketfd);
}

/// @brief Envoie une exception de type Init_serv_error et ferme correctemen le serveru (car sa ne passera pas automatiquemetn pas le destructeur)
/// @param msg le message de lexception
void Server::_throw_except(const std::string &msg)
{
	if (_socketfd != -1)
		close(_socketfd);
	throw Init_serv_error(msg);
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

void Server::_bind_and_listen()
{
	const sockaddr *sock_addr_serv_in_ptr = reinterpret_cast<const sockaddr *>(&this->_sock_addr_serv_in);

	// Configure l'option SO_REUSEADDR 
	int opt = REUSEADDR_OPTION;
	// Sa peret de dire que le port peut etre desactiver rapidement et reutiliser
	if (setsockopt(this->_socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		_throw_except("Erreur lors de la configuration de SO_REUSEADDR.");

	// Configure la socket en mode non-bloquant
	if (fcntl(this->_socketfd, F_SETFL, O_NONBLOCK) < 0)
		_throw_except("Erreur lors de la mise en mode non-bloquant de la socket.");


	// Associe la socket fd a la structure de sockaddr_in
	if (bind(this->_socketfd, sock_addr_serv_in_ptr, sizeof(this->_sock_addr_serv_in)) < 0)
		_throw_except("Erreur lors de l'association de l'adresse à la socket.");
	std::cout << "Adresse associée à la socket avec succès." << std::endl;

	// Dis au fd decouter lentre du port
	if (listen(this->_socketfd, SOMAXCONN) < 0)
		_throw_except("Erreur lors de la mise en écoute de la socket.");
	std::cout << "Socket en écoute sur le port " << this->get_port() << "." << std::endl;
}

void	Server::_paramEPoll(void)
{
	_epollfd = epoll_create1(0);
	if (_epollfd == -1)
		_throw_except("Erreur lors de la création de epoll");

	epoll_event ev;
	ev.events = EPOLLIN; // Surveiller les événements de lecture
	ev.data.fd = _socketfd; // Associer l'événement à la socket serveur

	if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _socketfd, &ev) == -1)
		_throw_except("Erreur lors de l'ajout de la socket serveur à epoll");
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

	this->_bind_and_listen();
	this->_paramEPoll();
	std::cout << getColorCode(GREEN) << "Construction Fini" << getColorCode(NOCOLOR) << std::endl;

}

int Server::_handle_client(int client_fd)
{
	char buffer[BUFFER_SIZE] = {0};
	ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);

	if (bytes_read <= 0)
	{
		// Déconnexion ou erreur
		std::cout << "Client déconnecté: " << client_fd << std::endl;
		close(client_fd);

		// Retirer le client de epoll
		epoll_ctl(_epollfd, EPOLL_CTL_DEL, client_fd, NULL);
		return (0);
	}

	std::cout << "Message reçu de " << client_fd << ": " << buffer << std::endl;

	// Répondre au client
	const char* response = "Message reçu";
	send(client_fd, response, strlen(response), 0);
	if (std::string(buffer) == "exit\n")
	{
		close(client_fd);
		// Retirer le client de epoll
		epoll_ctl(_epollfd, EPOLL_CTL_DEL, client_fd, NULL);
		return (1);
	}
	return (0);
}


// utiliser epoll et comprendre fonctionement
void	Server::exec(void)
{
	std::cout << getColorCode(YELLOW) << "Execution du Serveur ..." << getColorCode(NOCOLOR) << std::endl;

	epoll_event events[MAX_EVENTS]; // Tableau pour stocker les événements

	while (true)
	{
		int nfds = epoll_wait(_epollfd, events, MAX_EVENTS, -1); // Attendre les événements
		if (nfds == -1)
		{
			std::cerr << "Erreur dans epoll_wait" << std::endl;
			break;
		}

		for (int i = 0; i < nfds; ++i)
		{
			if (events[i].data.fd == _socketfd)
			{
				// Nouvelle connexion
				sockaddr_in client_addr;
				socklen_t client_len = sizeof(client_addr);
				int client_fd = accept(_socketfd, (struct sockaddr*)&client_addr, &client_len);
				if (client_fd == -1)
				{
					std::cerr << "Erreur d'acceptation de la connexion" << std::endl;
					continue;
				}

				std::cout << "Nouvelle connexion acceptée: " << client_fd << std::endl;

				// Ajouter le client à epoll
				epoll_event ev;
				ev.events = EPOLLIN; // Surveiller les événements de lecture
				ev.data.fd = client_fd;

				if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, client_fd, &ev) == -1)
				{
					std::cerr << "Erreur lors de l'ajout du client à epoll" << std::endl;
					close(client_fd);
				}
			}
			else
			{
				// Gérer les données du client
				if (_handle_client(events[i].data.fd) == 1)
					return;
				show_epollfd_data(std::cout, this->get_epollfd());
			}
		}
	}
}

Server::~Server()
{
	std::cout << getColorCode(RED) << "DEstructeur de Server" << getColorCode(NOCOLOR) << std::endl;
	if (this->_epollfd > -1)
		close(_epollfd);
	if (this->_socketfd > -1)
		close(this->_socketfd);
}

void show_epollfd_data( std::ostream & o, int const & epollfd)
{
	o << getColorCode(YELLOW) << "Le file descriptor epoll = " << getColorCode(BLUE) << epollfd << getColorCode(NOCOLOR) << std::endl;

	o << getColorCode(YELLOW) << "Événements surveillés par epoll :" << getColorCode(NOCOLOR) << std::endl;

	// Affichage des descripteurs surveillés
	struct epoll_event events[MAX_EVENTS];
	int nfds = epoll_wait(epollfd, events, MAX_EVENTS, 0); // Non-bloquant pour obtenir les descripteurs
	if (nfds == -1)
		o << getColorCode(RED) << "Erreur lors de la récupération des descripteurs epoll." << getColorCode(NOCOLOR) << std::endl;
	else if (nfds == 0)
		o << getColorCode(YELLOW) << "Aucun descripteur surveillé actuellement." << getColorCode(NOCOLOR) << std::endl;
	else
	{
		for (int i = 0; i < nfds; ++i)
		{
			o << getColorCode(YELLOW) << "Descripteur : " << getColorCode(BLUE) << events[i].data.fd << getColorCode(NOCOLOR);
			o << getColorCode(YELLOW) << " | Événements : " << getColorCode(BLUE);
			if (events[i].events & EPOLLIN) o << "EPOLLIN ";
			if (events[i].events & EPOLLOUT) o << "EPOLLOUT ";
			if (events[i].events & EPOLLERR) o << "EPOLLERR ";
			if (events[i].events & EPOLLHUP) o << "EPOLLHUP ";
			o << getColorCode(NOCOLOR) << std::endl;
		}
	}
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
	// Informations sur epoll
	show_epollfd_data(o, serv.get_epollfd());

	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	return o;
}