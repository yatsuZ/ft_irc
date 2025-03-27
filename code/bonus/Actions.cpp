/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actions.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:00:09 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/27 15:25:10 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* Actions du bot */

// TO DO: get lobby 
void	Bot::_manage_actions(std::string m)
{
	// std::cout << "###############" << std::endl;
	// std::cout << m << std::endl;

	std::vector<std::string> split_m = ft_split(m, "\r\n");
	//to do set message selon lobby

	for(size_t i=0; i<split_m.size(); i++)
	{
		if (split_m[i].size())
			std::cout << split_m[i] << std::endl;
		if (split_m[i].find("PING") != std::string::npos)
			_pong(split_m[i]);
		else if (split_m[i].find("JOIN :#") != std::string::npos)
			_welcome(split_m[i]);
		else if (split_m[i].find("PART #") != std::string::npos)
			_goodbye(split_m[i]);
		else if (_find_bword(split_m[i]))
			_kick(split_m[i]);
	}
}

void	Bot::_pong(std::string m)
{
	size_t pos = m.find("PING ");
	std::cout << "PONG " << m.substr(pos) << std::endl;
	send_message(std::string("PONG " + m.substr(pos)) + CRLF);
}

// greet new user in chan
void	Bot::_welcome(std::string m)
{
	// std::cout << "----------Message read--------------" << std::endl;
	// std::cout << "{" << m << "}" << std::endl;
	// std::cout << "----------Message end --------------" << std::endl;
	if (get_sender(m) == this->_nick)	
		send_message(std::string("PRIVMSG " + get_lobby(m) + " :Everybody welcome our fellow newcomer.. ME !!!") + CRLF);
	else
		send_message(std::string("PRIVMSG " + get_lobby(m) + " :Everybody welcome our fellow newcomer.. " + get_sender(m)) + CRLF);
}

void	Bot::_goodbye(std::string m)
{
	send_message(std::string("PRIVMSG " + get_lobby(m) + " :Everybody say goodbye to " + get_sender(m)) + CRLF);

}

bool	Bot::_find_bword(std::string m)
{
	for (size_t i=0; i<_banned_words.size(); i++)
	{
		if (m.find(_banned_words[i]) != std::string::npos)
			return 1;
	}
	return 0;
}

void	Bot::_kick(std::string m)
{
	send_message(std::string("KICK " + get_lobby(m) + " " +  get_sender(m) + " :got kicked for bad conduct x_x plz behave next time ^^") + CRLF);
}

void	Bot::_help(std::string m)
{
	std::string message;
	message.append("PRIVMSG ");
	message.append(get_lobby(m));
	message.append(" :list of cmd availables:time"); 
	send_message(message + CRLF);
}
