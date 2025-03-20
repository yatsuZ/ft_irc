
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:26 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/20 15:35:19 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Bonus.hpp"

class Bot
{
private:
	std::string							_ip;
	uint16_t 							_port; 		// Port d'écoute du serveur
	std::string							_password;
	std::string							_nick;
	std::string							_username;
	std::string							_hostname;
	std::string							_realname;
	std::string							_channel;	//liste channels a join "chan1,chan2,..."
	int									_socketfd;	// Le descripteur de la socket
	sockaddr_in							_sock_addr;	// Adresse de la socket du serveur

	std::map<std::string, std::string>	_infos;		//parse des infos de config dedans
	
	//connexion et communication avec le serveur
	void	send_message(const std::string & message);

	// actions
	// void	_time();
	// void	_kick();
	// void	_welcome();
	// void

	//connexion/deconnexion
	void	init();
	void	_connexion();	//envoi des infos du bot au serv
	void	_disconnect();

	//check
	void		_parse(char *);
	void		_map_info(std::string);
	void		_set_infos();
	uint16_t	_valid_port(std::string);

	//err
	void	_throw_msg(const std::string &);

public:
	Bot();
	Bot(int argc, char **argv);                                               
	~Bot();


};

//
class	InitException : public std::exception
{
private:
	const	std::string	_message;
public:
	InitException(std::string m) : _message(m){}
	virtual	~InitException() throw(){}
	virtual const char * what() const throw(){return _message.c_str();}
};