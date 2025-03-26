/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actions.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:00:09 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/26 22:29:17 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* Actions du bot */

// TO DO: get lobby 
void	Bot::_manage_actions(std::string m)
{
	//to do set message selon lobby
	if (m.find("JOIN :#") != std::string::npos)
		_welcome(m);
	if (m.find("PART #") != std::string::npos)
		_welcome(m);
	if (m.find("!!help") != std::string::npos)
		_help(m);
	if (_find_bword(m))
		_kick(m);
	if(m.find("!!quit") != std::string::npos)
		disconnect();
}

// greet new user in chan
void	Bot::_welcome(std::string m)
{
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
	std::cout << "=" << m << "=" << std::endl;
	send_message(std::string("PRIVMSG  " + get_lobby(m) + " :Not good " + get_sender(m) + " you'll get punished ...") + CRLF);
	send_message(std::string("KICK " + get_lobby(m)  +  get_sender(m) + " :You got kicked for bad conduct x_x plz behave next time ^^") + CRLF);
	send_message(std::string("PRIVMSG " + get_sender(m) + " :You got kicked for bad conduct x_x plz behave next time ^^") + CRLF);

}

void	Bot::_help(std::string m)
{
	std::string message;
	message.append("PRIVMSG ");
	message.append(get_lobby(m));
	message.append(" :list of cmd availables:time"); 
	send_message(message + CRLF);
}



// void	Bot::_ask(std::string m)
// {
// 	//randomize  numerous answers
// 	send_message(std::string("PRIVMSG #lobby :Ask your mother ") + get_sender(m) + CRLF);
// }