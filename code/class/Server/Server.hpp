/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:22:39 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/16 00:25:19 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"

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
	const unsigned long			_port;
	const std::string			_mot_de_passe;

	unsigned long	_is_a_legit_port(std::string &argv1);
	std::string	_is_a_legit_mdp(std::string &argv2);
	Server();

public:
	Server(std::string argv1, std::string argv2);
	~Server();

	std::string	get_name(void) const {return _name;}
	std::string	get_mdp(void) const {return _mot_de_passe;}
	unsigned long	get_port(void) const{return _port;}
};

std::ostream & operator<<( std::ostream & o, Server const & serv);

