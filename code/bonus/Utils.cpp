/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:43:51 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/23 16:44:56 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

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
