/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:22:39 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/23 18:37:59 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../Cmd_irssi/Cmd_irssi.hpp"
#include "./../Data_buffer/Data_buffer.hpp"


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
protected:

	const std::string			_name;				// Nom du serveur
	const uint16_t 				_port;				// Port d'écoute du serveur
	const std::string			_mot_de_passe;		// Mot de passe du serveur IRC
	const int					_socketfd;			// Le descripteur de la socket
	sockaddr_in					_sock_addr_serv_in;	// Adresse de la socket du serveur
	std::vector<struct pollfd> 	_all_pollfd;		// Vecteur de pollfd pour gérer plusieurs connexions

	uint16_t 		_is_a_legit_port(std::string &argv1);
	std::string		_is_a_legit_mdp(std::string &argv2);
	int				_init_socket(void);
	void 			_bind_and_listen(void);
	void			_throw_except(const std::string &msg);
	void			_paramPoll(void);

	Server();

public:
	Server(std::string & argv1, std::string & argv2);
	~Server();

	std::string					get_name(void) const {return _name;}
	std::string					get_mdp(void) const {return _mot_de_passe;}
	uint16_t 					get_port(void) const{return _port;}
	int							get_socketfd(void) const{return _socketfd;}
	sockaddr_in					get_socke_addr_serv(void) const{return _sock_addr_serv_in;}
	std::vector<struct pollfd>	get_pollfds(void) const {return this->_all_pollfd;}
	

	virtual void exec(void) = 0;

};

/// @brief Affiche tout les attributs de tout les pollfd du vecteur
std::ostream & operator<<(std::ostream &o, std::vector<struct pollfd> const &pollfds);
/// @brief Affiche tout les attributs de la class serveur
std::ostream & operator<<( std::ostream & o, Server const & serv);

