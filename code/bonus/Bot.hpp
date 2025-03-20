/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:26 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/20 14:05:14 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Bonus.hpp"

class Bot
{
public:
	Bot();

	~Bot();

	std::string	get_nick()const{return _nick;}

private:
	std::string			_nick;
	std::string			_username;
	std::string			_realname;
	std::string			_ip;
	uint16_t 			_port;		// Port d'écoute du serveur
	int					_socketfd;	// Le descripteur de la socket
	sockaddr_in			_sock_addr;	// Adresse de la socket du serveur
	std::string			_password;
	
	//connexion et communication avec le serveur
	void	_init();
	// void	_send_message();

	// actions
	// void	_time();
	// void	_kick();
	// void	_welcome();
	void	_disconnect();

	//check
	void	_valid_port();

	//err
	void	_throw_msg(const std::string &);

};

class	InitException : public std::exception
{
private:
	const	std::string	_message;
public:
	InitException(std::string m) : _message(m){}
	virtual	~InitException() throw(){}
	virtual const char * what() const throw(){return _message.c_str();}
};