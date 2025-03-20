/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:35:23 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/20 21:06:27 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(int argc, char **argv)
{
	std::cout << BPNK << "### Création du bot..." << RST << std::endl;
	if (argc != 2)
		throw InitException("==== Error: configuration file recquired.");
	_parse(argv[1]);
	init();
	(void)argv;

}

Bot::~Bot()
{
	if (_socketfd == -1)
		close(_socketfd);
	std::cout << BCYN << "### GOOD BYE ^^!" << RST << std::endl;
}

void	Bot::_parse(char *filename)
{
	std::cout << BPNK << "### Verifications des infos de configuration..." << RST <<std::endl;
	std::ifstream	file;
	std::string		line;

	file.open(filename, std::ifstream::in);
	if (!file.good())
		throw InitException("==== Error: can't read config file.");
	
	std::getline(file, line);
	while (file.good())
	{
		if (line.find("#", 0) == std::string::npos)
			_map_info(line);
		std::getline(file, line);
	}
	_set_infos();
}

//set les infos du fichier config dans une map
void	Bot::_map_info(std::string line)
{
	size_t								sep;
	std::string 						cmd;
	std::string							arg;

	if (line.empty())
		return ;
	sep = line.find("=");
	if (sep == std::string::npos)
		return;

	cmd = line.substr(0, sep);
	arg = line.substr(sep + 1);

	_infos.insert(std::pair<std::string, std::string>(cmd, arg));
}

void	Bot::_set_infos()
{
	std::cout  << BPNK << "### Initialisation des infos..." << RST << std::endl;

	_ip = _infos["ip"];
	_port = _valid_port(_infos["port"]);
	_password = _infos["password"];
	_nick = _infos["nick"];
	_username = _infos["username"];
	_hostname = _infos["hostname"];
	_realname = _infos["realname"];

	if (_ip.empty() || _password.empty() || _nick.empty() || _nick.empty() ||
		_username.empty() || _hostname.empty() || _realname.empty())
		throw InitException("==== Error: Invalid input in config file.");
}

void	Bot::init()
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
		throw InitException("====Error: can't connect to the server");	

	_connexion();
	//connexion au serveur
	std::cout << BCYN << "### Bot connected succesfully !" << RST << std::endl;
}

//send toutes les infos de connexion en tant qu'userBot au serveur
void	Bot::_connexion()
{	

	//CMDS IRC pour établir une connexion en tant qu'user en tant qu'user
	send_message("PASS " + _password + CRLF);
	send_message("NICK " + _nick + CRLF);
	send_message("USER " + _username + " " + _hostname + " " + _ip + " :" + _realname +  CRLF);
}

void	Bot::_disconnect()
{	
	close(_socketfd);
	return ;
}

uint16_t	Bot::_valid_port(std::string p)	//check si port valide
{
	long		port = atol(p.c_str());

	if (port < 1 || port > 65535)
		throw InitException("==== Error: Invalid Port (number should be between 1 and 65535).");

	return (static_cast<uint16_t>(port));
}

//excpetion message
void	Bot::_throw_msg(const std::string & m)
{
	if (_socketfd == -1)
		close(_socketfd);
	throw InitException(m);
}

// std::string::length retourne la len d'un strung en terme de bytes
void	Bot::send_message(const std::string & message)
{

	send(_socketfd, message.c_str(), message.size(), 0);
}