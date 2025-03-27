
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:43:51 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/26 04:37:06 by kuro             ###   ########.fr       */
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

	// std::cout << "cmd = " << cmd << std::endl;
	// std::cout << "arg = " << arg << std::endl;

	_infos.insert(std::pair<std::string, std::string>(cmd, arg));
}

void	Bot::_set_infos()
{
	std::string	tmp = "";
	std::cout  << BPNK << "### Initialisation des infos..." << RST << std::endl;

	_ip = _infos["ip"];
	_port = _valid_port(_infos["port"]);
	_password = _infos["password"];
	_nick = _infos["nick"];
	_username = _infos["username"];
	_hostname = _infos["hostname"];
	_realname = _infos["realname"];
	_channels = _infos["channels"];

	tmp = _infos["banned_words"];
	_banned_words = ft_split(tmp, " ");


	if (_ip.empty() || _password.empty() || _nick.empty() || _nick.empty() ||
		_username.empty() || _hostname.empty() || _realname.empty() || _channels.empty() || _banned_words.empty())
		throw InitException("==== Error: Invalid input in config file.");
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
	if (_socketfd != -1)
		close(_socketfd);
	throw InitException(m);
}

void	Bot::send_message(std::string message)
{
	send(_socketfd, message.c_str(), message.size(), 0);
}

std::string	Bot::get_sender(std::string msg)
{
	if (msg.find("PRIVMGS"))
	{
		size_t sep = msg.find("!");
		return (std::string(msg.substr(1, sep - 1)));
	}	
	return ("");
}

//fonctionne avec "{:Zero!~zyscb@127.0.0.1 JOIN :#lobby
//}"....update casse parfois ????????
std::string	Bot::get_lobby(std::string msg)
{
	size_t	pos = msg.find("#");

	if (pos != std::string::npos)
	{
		std::string	chan = msg.substr(pos);

		size_t	end_chan = chan.find_first_of(" \r\t\n\0");
		
		if (end_chan != std::string::npos)
			return chan.substr(0, end_chan);
		return (chan);
	}

	return ("");
}


//renvoie l'index du separateur dans &sep, - 1 si il trouve pas
ssize_t	Bot::is_sep(char c, std::string sep) 
{
	for(size_t i = 0; i< sep.size(); i++)
	{
		if (sep[i] == c)
			return i;
	}
	return -1;
}

std::vector<std::string> Bot::ft_split(const std::string & str, const std::string & sep)
{
	size_t						i;
	std::string					word;
	std::vector<std::string>	split;

	if (str.empty())
		return split;

	i=0;
	while (i < str.size())
	{
		if (is_sep(str[i], sep) != -1)
		{
			split.push_back(word);
			word.clear();
		}
		else
			word.push_back(str[i]);
		i++;
	}
	if (word.size() != 0)
	{
		split.push_back(word);
		word.clear();
	}
	return (split);
}

