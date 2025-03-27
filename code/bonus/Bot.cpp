/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:35:23 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/27 17:04:48 by yzaoui           ###   ########.fr       */
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
	
	_sock_addr.sin_addr.s_addr = inet_addr(_ip.c_str());
	_sock_addr.sin_family = AF_INET;
	_sock_addr.sin_port = htons(_port);


	my_poll_fd.fd = _socketfd;
	my_poll_fd.events = POLL_IN;
	my_poll_fd.revents = 0;

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
	// _is_logged = true;
}

std::string	Bot::recv_msg()
{
	char	buffer[BUFFERSIZE];
	ssize_t	bytes_recv = 0;
	
	bytes_recv = recv(_socketfd, buffer, BUFFERSIZE - 1, 0);

	if (bytes_recv <= 0)
		return "";

	buffer[bytes_recv] = '\0';

	return std::string(buffer);
}

void	Bot::execution()
{
	send_message(std::string("JOIN " + _channels) + std::string(CRLF));

	std::string	msg;
	
	while (1)
	{
		// Poll pour attendre un événement
		int ret = poll(&my_poll_fd, 1, 5); // Attente pour des événements +  Utilise _all_pollfd.data() pour obtenir un pointeur sur le tableau interne
		if (ret < 0)
			_throw_msg("Erreur de la fonction poll()");
		if (my_poll_fd.revents & POLLIN)
		{
			msg = recv_msg();
			if (msg.empty() || ft_shutdown(false))
				break;

			_manage_actions(msg);
		}
		
		
	}

	disconnect();
}

void	Bot::disconnect()
{	
	send_message(std::string("I will now disconnect... goodbye :') "));
	close(_socketfd);
	return ;
}

