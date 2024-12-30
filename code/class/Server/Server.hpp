/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:22:39 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/30 05:26:49 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"

#define ADDRESSE_IP_IN "127.0.0.1"
#define REUSEADDR_OPTION 1
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10


/// @brief Exception pour toutes erreurs provenant soit de l'initialisation de la classe Serveur ou provenant de la méthode Exec
class Init_serv_error : public std::exception
{
	private:
		const std::string	_msg;
	public :
		Init_serv_error(std::string msg): _msg(msg)
		{}
		virtual ~Init_serv_error() throw() {}
		virtual const char* what(void) const throw()
		{
			return (this->_msg.c_str());
		}
};

/// @brief Class Serveur : la classe principale qui gère tout, y compris la gestion des connexions et des échanges de données.
class Server
{
private:

	const std::string			_name;				// Nom du serveur
	const uint16_t 				_port;				// Port d'écoute du serveur
	const std::string			_mot_de_passe;		// Mot de passe du serveur IRC
	const int					_socketfd;			// Le descripteur de la socket
	sockaddr_in					_sock_addr_serv_in;	// Adresse de la socket du serveur
	std::vector<struct pollfd> 	_fds;				// Vecteur de pollfd pour gérer plusieurs connexions

	uint16_t 		_is_a_legit_port(std::string &argv1);
	std::string		_is_a_legit_mdp(std::string &argv2);
	int				_init_socket(void);
	void 			_bind_and_listen(void);
	void			_throw_except(const std::string &msg);
	void			_paramPoll(void);
	Server();

public:
	Server(std::string argv1, std::string argv2);
	~Server();

	std::string					get_name(void) const {return _name;}
	std::string					get_mdp(void) const {return _mot_de_passe;}
	uint16_t 					get_port(void) const{return _port;}
	int							get_socketfd(void) const{return _socketfd;}
	sockaddr_in					get_socke_addr_serv(void) const{return _sock_addr_serv_in;}
	std::vector<struct pollfd>	get_pollfds(void) const {return this->_fds;}

	void	exec(void);
};

/// @brief Affiche tout les attributs de tout les pollfd du vecteur
std::ostream & operator<<(std::ostream &o, std::vector<struct pollfd> const &pollfds);
/// @brief Affiche tout les attributs de la class serveur
std::ostream & operator<<( std::ostream & o, Server const & serv);

