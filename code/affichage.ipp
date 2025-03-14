/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:29:19 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/14 15:13:52 by yzaoui           ###   ########.fr       */
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
	if (act == PRIVMSG)
		o << "| the message : \"" << GREEN << cmd_irssi.get_message() << NOCOLOR << "\"";
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

std::ostream & operator<<( std::ostream & o, Mode const & mode)
{
	if (mode == I)
		o << "I";
	else if (mode == T)
		o << "T";
	else if (mode == K)
		o << "K";
	else if (mode == O)
		o << "O";
	else if (mode == L)
		o << "L";
	else
		o << "NO_MODE";
	return (o);
}

std::ostream & operator<<(std::ostream & o, std::vector<Mode> const & vec_of_mode)
{
	for (size_t i = 0; i < vec_of_mode.size(); i++)
	{
		if (i)
			o << ", " << vec_of_mode[i];
		else
			o << vec_of_mode[i];
	}
	return o;
}

std::ostream & operator<<(std::ostream & o, User const & user)
{
	o << "| " << YELLOW << "Nick: " << NOCOLOR << user.get_nick() << " | "
	  << YELLOW << "Name: " << NOCOLOR << user.get_name() << " | "
	  << YELLOW << "Hostname: " << NOCOLOR << user.get_hostname() << " | "
	  << YELLOW << "Real Name: " << NOCOLOR << user.get_realname() << " | "
	  << YELLOW << "Servername: " << NOCOLOR << user.get_servername() << " | "
	  << YELLOW << "Mode user: " << NOCOLOR << user.get_mode() << " | "
	  << YELLOW << "Servername: " << NOCOLOR << user.get_servername() << " | " 
	  << YELLOW << "the number of channels it has: " << NOCOLOR << user.get_chans().size() << " | "
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
	  << std::setw(10) << "Mode" 
	  << std::setw(10) << "Nbr chanelle" 
	  << std::endl;

	o << std::string(158, '-') << std::endl;

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
		  << std::setw(10) << userhuman.get_mode() 
		  << std::setw(10) << userhuman.get_chans().size() 
		  << std::endl;
	}

	return o;
}

std::ostream & operator<<( std::ostream & o, std::vector<size_t> const & vec_of_size_t)
{
	for (std::vector<size_t>::const_iterator i = vec_of_size_t.begin(); i != vec_of_size_t.end(); i++)
	{
		if (i != vec_of_size_t.begin())
			o << ", " << BLUE << *i << NOCOLOR;
		else
			o << GREEN << *i << NOCOLOR << " ";
	}
	return o;
}

std::ostream & operator<<(std::ostream & o, const Channel & c)
{
	o << c.get_name() << std::endl;
	o << "| " << YELLOW << "Name_chanelle: " << NOCOLOR << c.get_name() << " | "
	  << YELLOW << "Key: " << NOCOLOR << c.get_key() << " | "
	  << YELLOW << "Topic: " << NOCOLOR << c.get_topic() << " | "
	  << YELLOW << "Index user: " << NOCOLOR << c.get_index_users() << " | "
	  << YELLOW << "Index operators: " << NOCOLOR << c.get_index_operators() << " | "
	  << YELLOW << "All invite: " << NOCOLOR << c.get_user_invite() << " | "
	  << YELLOW << "nbr of user: " << NOCOLOR << c.get_nbr_of_user() << " / " << c.get_limit_user() << " | "
	  << YELLOW << "All mode: " << NOCOLOR << c.list_mode() << " | ";

	return o;
}


std::ostream & operator<<(std::ostream & o, std::vector<Channel> const & chanelle_list)
{
	if (chanelle_list.empty())
	{
		o << "Aucun channel." << std::endl;
		return o;
	}

	// Affichage du nombre total de channels
	o << "Nombre total de channels : " << chanelle_list.size() << std::endl;
	o << "____TOUT_LES_CHANELLES___ " << std::endl;

	for (size_t i = 0; i < chanelle_list.size(); ++i)
	{
		const Channel & c = chanelle_list[i];
		o << c << std::endl;
	}

	/*
	// En-tête du tableau
	o << std::left << std::setw(10) << "Index"
	<< std::setw(20) << "Nom"
	  << std::setw(15) << "Clé"
	  << std::setw(30) << "Topic"
	  << std::setw(20) << "Index Users"
	  << std::setw(20) << "Index Operators"
	  << std::setw(15) << "Nbr Users"
	  << std::setw(10) << "Limite"
	  << std::setw(15) << "Mode"
	  << std::endl;
	  
	  o << std::string(140, '-') << std::endl;
	  
	// Affichage des channels
	for (size_t i = 0; i < chanelle_list.size(); ++i)
	{
		const Channel & c = chanelle_list[i];
		
		o << std::left << std::setw(10) << i
		<< std::setw(20) << c.get_name()
		<< std::setw(15) << c.get_key()
		<< std::setw(30) << c.get_topic()
		<< std::setw(20) << c.get_index_users()
		<< std::setw(20) << c.get_index_operators()
		<< std::setw(15) << c.get_nbr_of_user()
		<< std::setw(10) << c.get_limit_user()
		<< std::setw(15) << c.get_mode()
		<< std::endl;
	}
	
	*/
	return o;
}

std::ostream & operator<<( std::ostream & o, std::vector<std::string> const & list_of_word)
{
	o << std::endl;
	size_t j = 0;
	for (std::vector<std::string>::const_iterator i = list_of_word.begin(); i != list_of_word.end(); i++)
	{
		o << "[" << j++ << "] = \"" << *i << "\"" << std::endl;
	}
	return (o);
}

std::ostream & operator<<( std::ostream & o, DCC_TOKEN const & dcc_token)
{
	if (dcc_token == SEND_DCC)
		o << "SEND";
	else if (dcc_token == GET_DCC)
		o << "GET";
	else if (dcc_token == IDK_DCC)
		o << "IDK";
	return (o);
}

std::ostream & operator<<( std::ostream & o, Dcc const & dcc)
{
	o << "dcc atribut = " << dcc.get_type() << " " << dcc.get_file_name() << " " << dcc.get_host() << " " << dcc.get_port() << " " << dcc.get_taille_du_fichier() 
	<< " emeteur[" << dcc.get_index_emeteur() << "] | recepteur[" << dcc.get_index_recepteur() << "]" << std::endl;
	return (o);
}

std::ostream & operator<<( std::ostream & o, std::vector<Dcc> const & list_dcc)
{
	for (size_t i = 0; i < list_dcc.size(); ++i)
	{
		o << "[" << RED << i << NOCOLOR << "] " << list_dcc[i] << std::endl;
	}
	return (o);
}
