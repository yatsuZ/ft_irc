/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:23:05 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/30 05:52:30 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

/// @brief verifier que argv1 est un port legit et return sa valeur en uint16_t  sinon envoie une exception, un bon port est compris entre 1 et 65535
/// @param argv1 Le premier arguement qui est un port en string
/// @return uint16_t le port par argv1
uint16_t  Server::_is_a_legit_port(std::string & argv1)
{
	// for (size_t i = 0; i < argv1.size(); ++i) {
	// 	if (!std::isdigit(argv1[i]))
	// 		throw Init_serv_error("Le premier argument : \"" + argv1 + "\" n'est pas un nombre valide.");
	// }

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

/// @brief Constructeur du serveur
/// @param argv1 Le port qui sera parser et configurer en temp que _port
/// @param argv2 Le mot de passe du serveur qui sera stockée dans _mdp
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
	
	this->_paramPoll();
	
	std::cout << getColorCode(GREEN) << "Construction Fini" << getColorCode(NOCOLOR) << std::endl;

}

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
	std::cout << "Adresse associée à la socket avec succès." << std::endl;

	// Dis au fd decouter lentre du port
	if (listen(this->_socketfd, SOMAXCONN) < 0)
		_throw_except("Erreur lors de la mise en écoute de la socket.");
	std::cout << "Socket en écoute sur le port " << this->get_port() << "." << std::endl;
}

void	Server::_paramPoll(void)
{
	// Structure pour poll
	struct pollfd server_pollfd;

	server_pollfd.fd = _socketfd;	// La socket du serveur
	server_pollfd.events = POLLIN;	// On surveille les événements de lecture (connexion entrante)
	server_pollfd.revents = 0;
	_fds.push_back(server_pollfd);
}

/// @brief Methode qui est le coeur du programme
void	Server::exec(void)
{
	std::cout << getColorCode(YELLOW) << "Execution du Serveur ..." << getColorCode(NOCOLOR) << std::endl;

	// Boucle principale
	while (true)
	{
		// Poll pour attendre un événement
		int ret = poll(this->_fds.data(), 1, 5); // Attente infinie pour des événements +  Utilise _fds.data() pour obtenir un pointeur sur le tableau interne
		if (ret < 0)
			this->_throw_except("Erreur de la fonction poll()");
		// Vérification si la socket serveur est prête à accepter une connexion
		if (this->_fds[0].revents & POLLIN)
		{
			sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			int client_fd = accept(_socketfd, (struct sockaddr*)&client_addr, &client_len);
			if (client_fd < 0)
			{
				std::cerr << getColorCode(RED) << "Erreur d'acceptation de la connexion" << getColorCode(NOCOLOR) << std::endl;
				break;
			}
			std::cout << getColorCode(GREEN) << "Connexion acceptée!" << getColorCode(NOCOLOR) << std::endl;

			// Lire les données envoyées par le client
			char buffer[BUFFER_SIZE] = {0};
			ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
			{
				std::cerr << getColorCode(RED) << "Erreur de lecture des données" << getColorCode(NOCOLOR) << std::endl;
				close(client_fd);
				break;
			}
			// std::cout << "BUFFER = \"" << buffer << "\"" << std::endl;
			if (std::string(buffer) == "exit\n")
			{
				close(client_fd);
				break;
			}
			std::cout << getColorCode(CYAN) << "Message reçu: " << getColorCode(NOCOLOR) << getColorCode(MAGENTA) << buffer << getColorCode(NOCOLOR) << std::endl;

			// Répondre au client
			const char* response = "Message reçu";
			send(client_fd, response, strlen(response), 0);
			std::cout << getColorCode(GREEN) << "Réponse envoyée au client" << getColorCode(NOCOLOR) << std::endl;

			// Fermer la connexion avec le client
			close(client_fd);
		}
	}
	std::cout << getColorCode(YELLOW) << "FIN DU SERVEUR" << getColorCode(NOCOLOR) << std::endl;
}

Server::~Server()
{
	std::cout << getColorCode(RED) << "DEstructeur de Server" << getColorCode(NOCOLOR) << std::endl;
	if (this->_socketfd > -1)
		close(this->_socketfd);
}

std::ostream &operator<<(std::ostream &o,std::vector<struct pollfd> const &pollfds)
{
	o << getColorCode(YELLOW) << "Liste des pollfd surveillés :" << getColorCode(NOCOLOR) << std::endl;
	for (size_t i = 0; i < pollfds.size(); ++i)
	{
		o << getColorCode(CYAN) << "Pollfd #" << i << ":" << getColorCode(NOCOLOR) << std::endl;
		struct pollfd current_poll_fd = pollfds[i];
		o << getColorCode(YELLOW) << "\tFile Descriptor: " << getColorCode(BLUE) << current_poll_fd.fd << getColorCode(NOCOLOR) << std::endl;
		o << getColorCode(YELLOW) << "\tEvents: " << getColorCode(BLUE) << current_poll_fd.events << getColorCode(NOCOLOR) << " (";
	
		// Affichage détaillé des événements surveillés
		if (current_poll_fd.events & POLLIN) o << "POLLIN";
		if (current_poll_fd.events & POLLOUT) o << "POLLOUT";
		if (current_poll_fd.events & POLLERR) o << "POLLERR";
		if (current_poll_fd.events & POLLHUP) o << "POLLHUP";
		if (current_poll_fd.events & POLLNVAL) o << "POLLNVAL";
		o << ")" << std::endl;
	
		o << getColorCode(YELLOW) << "\tRevents: " << getColorCode(BLUE) << current_poll_fd.revents << getColorCode(NOCOLOR) << " (";
	
		// Affichage détaillé des événements retournés
		if (current_poll_fd.revents & POLLIN) o << "POLLIN";
		if (current_poll_fd.revents & POLLOUT) o << "POLLOUT";
		if (current_poll_fd.revents & POLLERR) o << "POLLERR";
		if (current_poll_fd.revents & POLLHUP) o << "POLLHUP";
		if (current_poll_fd.revents & POLLNVAL) o << "POLLNVAL";
		o << ")" << std::endl;
	}
	return o;
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
	// Affichage des pollfds
	o << serv.get_pollfds() << std::endl;
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	return o;
}

