/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Actions.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:00:09 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/23 21:37:42 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

/* Actions du bot */

// TO DO: get lobby 
void	Bot::_manage_actions(std::string m)
{
	//to do set message selon lobby
	if (m.find("JOIN"))
		_welcome(m);
	if (m.find("!!help"))
		_help(m);
	if (m.find("!!time"))
		_time(m);
	if (m.find("!!ask"))
		_ask(m);
	if (m.find(_banned_words))
		_kick(m);
	if(m.find("!!quit"))
		_disconnect();
}
// greet new user in chan
void	Bot::_welcome(std::string m)
{
	send_message(std::string("PRIVMSG #lobby :Everybody welcome our fellow newcomer.. ") + get_sender(m) + " !!!" + CRLF);
}

void	Bot::_time(std::string m)
{
	(void)m;
	std::cout << "Not setted yet" << std::endl;
	send_message(std::string("PRIVMSG #lobby :Time not setted yet") + CRLF);
	//RPL_TIME 391
	//set TS
}

void	Bot::_ask(std::string m)
{
	//randomize  numerous answers
	send_message(std::string("PRIVMSG #lobby :Ask your mother ") + get_sender(m) + CRLF);
}

void	Bot::_kick(std::string m)
{
	send_message(std::string("PRIVMSG #lobby :Not good " + get_sender(m) + " you'll get punished ..." + CRLF));
	//send KICK cmd
}

void	Bot::_help(std::string m)
{
	(void)m;
	send_message(std::string("PRIVMSG #lobby :help not set yet") + CRLF);
}