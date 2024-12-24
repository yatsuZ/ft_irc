/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:22:39 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/24 08:13:07 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"

#define ADDRESSE_IP_IN "127.0.0.1"
#define REUSEADDR_OPTION 1
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10

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

class Server
{
private:

	const std::string			_name;
	const uint16_t 				_port;
	const std::string			_mot_de_passe;
	const int					_socketfd;
	sockaddr_in					_sock_addr_serv_in;
	struct pollfd 				_fds[MAX_EVENTS];


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

	std::string				get_name(void) const {return _name;}
	std::string				get_mdp(void) const {return _mot_de_passe;}
	uint16_t 				get_port(void) const{return _port;}
	int						get_socketfd(void) const{return _socketfd;}
	sockaddr_in				get_socke_addr_serv(void) const{return _sock_addr_serv_in;}


	void	exec(void);
};

std::ostream & operator<<( std::ostream & o, Server const & serv);

