/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:20:33 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/01 01:05:55 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"


static bool target_is_chanelle(std::string & arg1)
{
	if (arg1.size() == 1 || (arg1.size() == 2 && arg1[0] == '@'))
		return (false);
	else if (arg1[0] == '#' || (arg1[0] == '@' && arg1[1] == '#'))
		return (true);
	return (false);
}

// message envoyer : :<nick>!~<username>@<hostname> PRIVMSG <CIBLE> :<msg>
// message recu    : PRIVMSG <cible> :<msg>

Reaction_Serv	Irssi_serv::ft_privmsg(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::string reply;
	std::cout << YELLOW << "-------- PRIVMSG -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	// 1. verifier si le user existe ou est ban
	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));
	// else if ()// VERIFIER QUIL EST PAS BANN // SAMIRA ici

	if (current_cmd.get_arg().size() < 1)
	{
		send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd);
		return (NONE);
	}
	std::string name_target = current_cmd.get_arg()[0];
	
	bool only_operator = false;
	if (target_is_chanelle(name_target))//is chanelle
	{
		if (name_target[0] == '@')// verifier si sa commence par un @ pour les ops
		{
			name_target.erase(name_target.begin());
			only_operator = true;
		}

		Channel * target_chan = this->_find_chan_in_user_by_name(*current_user, name_target);
		if (!target_chan)
			return (send_message(ERR_CANNOTSENDTOCHAN(std::string(SERVER_NAME), current_cmd.get_arg()[0]), current_pollfd), (NONE));
		reply = PRIVMSG_REP(
			current_user->get_nick(), 
			current_user->get_name(), 
			current_user->get_hostname(), 
			current_cmd.get_arg()[0], 
			current_cmd.get_message()
		);

		// if (only_operator)// Verifier si il a droit sam
		this->_send_message_to_a_chanelle(*current_user, *target_chan, reply, only_operator);
	}
	else
	{
		UserHuman * target_user = this->_get_userhuman_by_nick(name_target);
		if (!target_user)
			return (send_message(ERR_NOSUCHNICK(this->get_name(), name_target), current_pollfd), (NONE));
		reply = PRIVMSG_REP(
			current_user->get_nick(), 
			current_user->get_name(), 
			current_user->get_hostname(), 
			name_target, 
			current_cmd.get_message()
		);	
		send_message(reply, this->_all_pollfd[target_user->get_index_pollfd()]);
	}

	return (NONE);
}
