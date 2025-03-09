/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:49:24 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/09 20:20:27 by smlamali         ###   ########.fr       */
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
		if (current_chan->get_topic().empty())
			return (send_message(RPL_NOTOPIC(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), NONE);
		send_message(RPL_TOPIC(this->get_name(), current_user->get_nick(), current_chan->get_name(), current_chan->get_topic()), current_pollfd);
		send_message(RPL_TOPICWHOTIME(this->get_name(), current_user->get_nick(), current_chan->get_name(), current_chan->get_autor_topic(), current_chan->time_creation_in_string()), current_pollfd);
		return (NONE);
	}

	int res = _is_op_in_chan(*current_user, *current_chan);
	if (res == -1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick()), current_pollfd), (NONE));
	else if (res == -2)
		return (send_message(ERR_NOTONCHANNEL(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	else if (res == -3 && !current_chan->mode_in_channel(T))
	 	return (send_message(ERR_CHANOPRIVSNEEDED(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));

	std::string new_topic = current_cmd.get_message();
	std::string new_author = current_user->get_nick();
	time_t		new_time_creation = std::time(NULL);
	
	current_chan->set_topic(new_topic);
	current_chan->set_autor_topic(new_author);
	current_chan->set_creation_topic(new_time_creation);

	_send_message_to_a_chanelle(*current_user, *current_chan, NEW_TOPIC(current_user->get_nick(), current_user->get_name(), current_user->get_hostname(), current_chan->get_name(), current_chan->get_topic()));
	
	return (send_message(NEW_TOPIC(current_user->get_nick(), current_user->get_name(), current_user->get_hostname(), current_chan->get_name(), current_chan->get_topic()), current_pollfd), (NONE));
}
