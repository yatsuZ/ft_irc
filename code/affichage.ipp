/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:29:19 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/23 12:50:44 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Metre le dernier fichier hpp qui reunnie tout les headers
#include "./class/Irssi_serv/Irssi_serv.hpp"

// Affichage de l'enum action en string
std::ostream & operator<<( std::ostream & o, Action const & action)
{
	o << std::string(getActionString(action));
	return (o);
}

// Affichage de l'enum color sa couleur
std::ostream & operator<<( std::ostream & o, Color const & color)
{
	o << std::string(getColorCode(color));
	return (o);
}

// Affichage d'un vecteur de pollfd leur chaque attribut du tableau
inline std::ostream &operator<<(std::ostream &o, std::vector<struct pollfd> const &pollfds)
{
	o << YELLOW << "Liste des pollfd surveillés, Le premier index est le socket le rest des clients :" << NOCOLOR << std::endl;

	printSeparator(o, 118);
	// Affichage de l'en-tête du tableau avec des largeurs ajustées
	o
	<< "| " << MAGENTA << std::setw(8) << std::left << "Index" << NOCOLOR
	<< "| " << RED << std::setw(20) << std::left << "File Descriptor" << NOCOLOR
	<< "| " << GREEN << std::setw(40) << std::left << "Events" << NOCOLOR
	<< "| " << NOCOLOR << std::setw(40) << std::left << "Revents" << NOCOLOR
	<< " |" << std::endl;

	// Utilisation de la fonction pour afficher la ligne de séparation
	printSeparator(o, 118);

	for (size_t i = 0; i < pollfds.size(); ++i)
	{
		struct pollfd current_poll_fd = pollfds[i];

		// Affichage de chaque ligne du tableau avec des largeurs ajustées
		o
		<< "| " << MAGENTA << std::setw(8) << std::left << i << NOCOLOR
		<< "| " << RED << std::setw(20) << std::left << current_poll_fd.fd << NOCOLOR
		<< "| " << GREEN << std::setw(40) << std::left << getEventsString(current_poll_fd.events )<< NOCOLOR
		<< "| " << NOCOLOR << std::setw(40) << std::left << getEventsString(current_poll_fd.revents )<< NOCOLOR
		<< " |" << std::endl;
	}

	// Dernière ligne de séparation
	printSeparator(o, 118);

	return o;
}

// Affichage de la class Serveur chacun de ces attribut
std::ostream	&operator<<( std::ostream & o, Server const & serv)
{
	sockaddr_in const &socket_adresse_in = serv.get_socke_addr_serv();
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &socket_adresse_in.sin_addr, ip_str, INET_ADDRSTRLEN);
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	o << "Voici Toutes les information du server" << std::endl;
	o << YELLOW << "Le nom du Serveur = " << BLUE << serv.get_name() << NOCOLOR << std::endl;
	o << YELLOW << "Le mot de passe du Serveur = " << BLUE << serv.get_mdp() << NOCOLOR << std::endl;
	o << YELLOW << "Le file descriptor du socket = " << BLUE << serv.get_socketfd() << NOCOLOR << std::endl;
	o << YELLOW << "Socket IN Adresse IP du serveur = " << BLUE << NOCOLOR << ip_str << std::endl;
	o << YELLOW << "Le port du Serveur = " << BLUE << serv.get_port() << NOCOLOR << std::endl;
	// o << YELLOW << "Le port du Serveur a parti de socket adresse in = " << BLUE << ntohs(socket_adresse_in.sin_port) << NOCOLOR << std::endl;
	// Affichage des pollfds
	o << serv.get_pollfds() << std::endl;
	o << "|----------------------------------------------------------------------------------------|" << std::endl;
	return o;
}

/// Affichage de la class template DataBuffer 
template <typename T>
std::ostream & operator<<( std::ostream & o, Data_buffer<T> const & data_buffer)
{
	o << "Data_buffer:" << std::endl;
	o << BLUE << "\t_value_type: " << NOCOLOR << data_buffer.get_type_string() << std::endl;
	o << BLUE << "\t_total_bytes_received: " << NOCOLOR << data_buffer.get_total_bytes_received() << std::endl;
	o << BLUE << "\t_data:" << NOCOLOR << " [";
	for (typename std::vector<T>::const_iterator it = data_buffer._data.begin();
		it != data_buffer._data.end(); ++it)
	{
		o << *it;
		if (it + 1 != data_buffer._data.end())
			o << ", ";
	}
	o << "]" << std::endl;
	return o;
}

// Affichage de la class Cmd_irssi chacun de ces attribut
std::ostream & operator<<( std::ostream & o, Cmd_irssi const & cmd_irssi)
{
	const std::string &cmd = cmd_irssi.get_cmd();
	const std::vector<std::string> &lst_cmd = cmd_irssi.get_arg();
	size_t taille_de_lst_cmd = lst_cmd.size();
	Action act = cmd_irssi.get_action();

	o << "cmd_irssi = ";
	if (cmd.empty())
		o << CYAN << "Pas de commande et ni d'argument" << NOCOLOR;
	else
	{
		o << "\"" << MAGENTA << cmd << NOCOLOR << "\" [ ";
		for (size_t index_arg = 0; index_arg < taille_de_lst_cmd; ++index_arg)
		{
			o << "\"" << YELLOW << lst_cmd[index_arg];
			if (index_arg + 1 < taille_de_lst_cmd)
				o << NOCOLOR << "\", ";
			else
			o << NOCOLOR << "\"";
		}
		o << " ]";
	}
	o << " -> " << RED << act << NOCOLOR;
	return o;
}

std::ostream & operator<<( std::ostream & o, Client const & client)
{
	sockaddr_in const &socket_adresse_client = client.get_client_addr();
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &socket_adresse_client.sin_addr, ip_str, INET_ADDRSTRLEN);

	o << "| " << "index pollfd = "	<< CYAN << client.get_index_pollfd() << NOCOLOR << " | "
	<< "client adresse = " 			<< CYAN << ip_str << "::" << ntohs(socket_adresse_client.sin_port) << NOCOLOR << " | "
	<< "taille de ladresse = "		<< CYAN << client.get_client_len() << NOCOLOR << " | "
	<< "est il connectée = " 		<< CYAN << client.get_is_connect() << NOCOLOR << " |";
	return o;
}

std::ostream & operator<<( std::ostream & o, Mode_User const modeu)
{
	if (modeu == NONE_MODE)
		o << "NONE_MODE";
	else if (modeu == I)
		o << "Invisible";
	return o;
}

std::ostream & operator<<(std::ostream & o, User const & user)
{
	o << "| " << YELLOW << "Nick: " << NOCOLOR << user.get_nick() << " | "
	  << YELLOW << "Name: " << NOCOLOR << user.get_name() << " | "
	  << YELLOW << "Hostname: " << NOCOLOR << user.get_hostname() << " | "
	  << YELLOW << "Real Name: " << NOCOLOR << user.get_realname() << " | "
	  << YELLOW << "Servername: " << NOCOLOR << user.get_servername() << " | "
	  << YELLOW << "Is Init: " << NOCOLOR << (user.get_is_init() ? "true" : "false");
	return o;
}

std::ostream & operator<<( std::ostream & o, UserHuman const & userhuman)
{
	o << static_cast<Client>(userhuman) << " " << static_cast<User>(userhuman);
	return o;
}

std::ostream & operator<<(std::ostream & o, std::vector<UserHuman> const & userhumans)
{
	if (userhumans.empty())
	{
		o << "Aucun utilisateur." << std::endl;
		return o;
	}

	// En-tête du tableau
	o << std::left << std::setw(10) << "Index"
	  << std::setw(18) << "IP:Port"
	  << std::setw(18)  << "index POLLFD"
	  << std::setw(15) << "Nick"
	  << std::setw(15) << "Name"
	  << std::setw(20) << "Hostname"
	  << std::setw(20) << "Real Name"
	  << std::setw(15) << "Servername"
	  << std::setw(10) << "Is Init" 
	  << std::endl;

	o << std::string(148, '-') << std::endl;

	// Affichage des utilisateurs
	for (size_t i = 0; i < userhumans.size(); ++i)
	{
		const UserHuman & userhuman = userhumans[i];

		// Récupération des informations de connexion

		o << std::left << std::setw(10) << i
		  << std::setw(18) << userhuman.get_ip_to_string() + ":" + userhuman.get_port_to_string()
		  << std::setw(18)  << userhuman.get_index_pollfd()
		  << std::setw(15) << userhuman.get_nick()
		  << std::setw(15) << userhuman.get_name()
		  << std::setw(20) << userhuman.get_hostname()
		  << std::setw(20) << userhuman.get_realname()
		  << std::setw(15) << userhuman.get_servername()
		  << std::setw(10) << (userhuman.get_is_init() ? "true" : "false")
		  << std::endl;
	}

	return o;
}

	// std::string					_name;
	// std::string					_key;
	// std::string					_topic;
	// std::vector<User> 			_users;
	// size_t						_limit_user;

	// std::vector<User>			_operators;
	// std::vector<Mode_Channel>	_mode; //?


std::ostream & operator<<(std::ostream & o, const Channel & c)
{
	o << c.get_name() << std::endl;
	return o;
}


std::ostream & operator<<(std::ostream & o, std::vector<Channel> const & chanelle_list)
{
	
}

