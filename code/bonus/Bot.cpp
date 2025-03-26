/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:35:23 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/26 05:09:43 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(int argc, char **argv) : _is_logged(false)
{
	std::cout << BPNK << "### Création du bot..." << RST << std::endl;
	if (argc != 2)
		throw InitException("==== Error: configuration file recquired.");
	_parse(argv[1]);
	_init();
}

Bot::~Bot()
{
	if (_socketfd != -1)
		close(_socketfd);
	std::cout << BCYN << "### GOOD BYE ^^!" << RST << std::endl;
}

void	Bot::_init()
{
	std::cout << BPNK <<"### Connexion au serveur..." << _nick << RST << std::endl;

	const sockaddr	*sock_addr_ptr = reinterpret_cast<const sockaddr *>(&_sock_addr);
	// (void)sock_addr_ptr;
	_socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketfd == -1)
		_throw_msg("==== Error: socket creation failed... -1");
	
	_sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(_port);

	if (connect(_socketfd, sock_addr_ptr, sizeof(*sock_addr_ptr)) == -1)
		_throw_msg("====Error: can't connect to the server");

	_connexion();

}

//send toutes les infos de connexion en tant qu'userBot au serveur
void	Bot::_connexion()
{	
	//CMDS IRC pour établir une connexion en tant qu'user en tant qu'user
	send_message("PASS " + _password + CRLF);
	send_message("NICK " + _nick + CRLF);
	send_message("USER " + _username + " " + _hostname + " " + _ip + " :" + _realname +  CRLF);
	std::cout << BCYN << "### Bot connected succesfully !" << RST << std::endl;
	_is_logged = true;
}

std::string	Bot::recv_msg()
{
	char	buffer[BUFFERSIZE];
	ssize_t	bytes_recv = 0;
	
	bytes_recv = recv(_socketfd, buffer, BUFFERSIZE, 0);

	if (bytes_recv <= 0)
		return "";

	buffer[bytes_recv] = '\0';

	return std::string(buffer);

}

void	Bot::execution()
{
	send_message(std::string("JOIN #lobby") + std::string(CRLF));

	std::string	msg;
	
	while (_is_logged)
	{
		msg = recv_msg();

		std::cout << "Message read:" << std::endl;
		std::cout << "[" << msg << "]" << std::endl;
		if (msg.empty())
			break;
		_manage_actions(msg);
	}

	disconnect();
}

void	Bot::disconnect()
{	
	send_message(std::string("I will now disconnect... goodbye :') "));
	close(_socketfd);
	return ;
}

