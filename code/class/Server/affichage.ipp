/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:29:19 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/13 01:07:37 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Server.hpp"

// Fonction pour convertir les événements en chaîne de caractères
static std::string getEventsString(short events)
{
	std::string events_str;
	if (events & POLLIN) events_str += "POLLIN ";
	if (events & POLLOUT) events_str += "POLLOUT ";
	if (events & POLLERR) events_str += "POLLERR ";
	if (events & POLLHUP) events_str += "POLLHUP ";
	if (events & POLLNVAL) events_str += "POLLNVAL ";

	return events_str.empty() ? "None" : events_str;
}

// Fonction pour générer une ligne de séparation
static void printSeparator(std::ostream &o, size_t width)
{
	o << "|" << std::string(width - 2, '-') << "|" << std::endl;
}

inline std::ostream &operator<<(std::ostream &o, std::vector<struct pollfd> const &pollfds)
{
	o << getColorCode(YELLOW) << "Liste des pollfd surveillés, Le premier index est le socket le rest des clients :" << getColorCode(NOCOLOR) << std::endl;

	printSeparator(o, 118);
	// Affichage de l'en-tête du tableau avec des largeurs ajustées
	o
	<< "| " << getColorCode(MAGENTA) << std::setw(8) << std::left << "Index" << getColorCode(NOCOLOR)
	<< "| " << getColorCode(RED) << std::setw(20) << std::left << "File Descriptor" << getColorCode(NOCOLOR)
	<< "| " << getColorCode(GREEN) << std::setw(40) << std::left << "Events" << getColorCode(NOCOLOR)
	<< "| " << getColorCode(NOCOLOR) << std::setw(40) << std::left << "Revents" << getColorCode(NOCOLOR)
	<< " |" << std::endl;

	// Utilisation de la fonction pour afficher la ligne de séparation
	printSeparator(o, 118);

	for (size_t i = 0; i < pollfds.size(); ++i)
	{
		struct pollfd current_poll_fd = pollfds[i];

		// Affichage de chaque ligne du tableau avec des largeurs ajustées
		o
		<< "| " << getColorCode(MAGENTA) << std::setw(8) << std::left << i << getColorCode(NOCOLOR)
		<< "| " << getColorCode(RED) << std::setw(20) << std::left << current_poll_fd.fd << getColorCode(NOCOLOR)
		<< "| " << getColorCode(GREEN) << std::setw(40) << std::left << getEventsString(current_poll_fd.events )<< getColorCode(NOCOLOR)
		<< "| " << getColorCode(NOCOLOR) << std::setw(40) << std::left << getEventsString(current_poll_fd.revents )<< getColorCode(NOCOLOR)
		<< " |" << std::endl;
	}

	// Dernière ligne de séparation
	printSeparator(o, 118);

	return o;
}


inline std::ostream	&operator<<( std::ostream & o, Server const & serv)
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
