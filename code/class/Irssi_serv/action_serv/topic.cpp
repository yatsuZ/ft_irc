/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:49:24 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/06 15:03:32 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_topic(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;
	std::cout << "-------- TOPIC -----------" << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));

	if (current_cmd.get_arg().size() == 0 || current_cmd.get_arg()[0][0] == ':')
		return (send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), (NONE));

	Channel * current_chan = _get_channel_by_name(current_cmd.get_arg()[0]);
	if (current_chan == NULL)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), current_cmd.get_arg()[0]), current_pollfd), NONE);
	else if (current_cmd.get_arg().size() == 1)
	{
		send_message(RPL_TOPIC(this->get_name(), current_user->get_nick(), current_chan->get_name(), current_chan->get_topic() + CRLF), current_pollfd);
		return (NONE);
	}

	std::string new_topic = current_cmd.get_message();
	
	
	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}
