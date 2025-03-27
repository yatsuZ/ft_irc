
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
#include "../class/Data_buffer/Data_buffer.hpp"

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
	std::string							_channels;	//liste chan to join join "chan1,chan2,..."
	int									_socketfd;	// Le descripteur de la socket
	sockaddr_in							_sock_addr;	// Adresse de la socket du serveur
	bool								_is_logged;

	struct pollfd my_poll_fd;
	
	std::vector<std::string>			_banned_words;
	std::map<std::string, std::string>	_infos;		//parse des infos de config dedans
	
	//connexion et communication avec le serveur
	void			send_message(std::string);
	std::string		recv_msg();
	std::string		get_sender(std::string);
	std::string		get_lobby(std::string);

	// actions
	void 	_manage_actions(std::string m);
	void	_help(std::string);
	//auto 
	void	_welcome(std::string);
	void	_goodbye(std::string m);
	void	_kick(std::string);
	void	_pong(std::string m);

	//connexion/deconnexion
	void		_init();
	void		_connexion();	//envoi des infos du bot au serv

	//check
	void		_parse(char *);
	void		_map_info(std::string);
	void		_set_infos();
	uint16_t	_valid_port(std::string);
	bool		_find_bword(std::string)
;
	//err
	void	_throw_msg(const std::string &);


	//utils
	ssize_t	is_sep(char, std::string);
	std::vector<std::string> ft_split(const std::string &, const std::string &);

public:
	Bot();
	Bot(int argc, char **argv);                                               
	~Bot();

	void		execution();
	void		disconnect();

	bool		get_log();
	bool		set_log();
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