/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:28:23 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/09 20:15:18 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_part(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << YELLOW << "-------- PART -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));

	if (current_cmd.get_arg().size() < 1 || current_cmd.get_arg()[0][0] == ':')
		return (send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), (NONE));

	std::vector<std::string> list_of_chan_to_part = ft_split(current_cmd.get_arg()[0], ",");
	
	for (size_t i = 0; i < list_of_chan_to_part.size(); i = (i + 2))
	{
		std::cout << current_user->get_nick() << " leave chan " << list_of_chan_to_part[i] << std::endl;
		Reaction_Serv res_serv = multiple_part(current_pollfd, *current_user, list_of_chan_to_part[i], current_cmd);
		if (res_serv != NONE)
			return (res_serv);
	}
	return (NONE);
}


/////

Reaction_Serv Irssi_serv::multiple_part(pollfd &current_pollfd, UserHuman & current_user, std::string & chan_name, Cmd_irssi &current_cmd)
{
	Channel * chan_to_part = _get_channel_by_name(chan_name);
	if (!chan_to_part)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user.get_nick(), chan_name), current_pollfd), (NONE));
	
	int target_is_in_chan = _is_op_in_chan(current_user, *chan_to_part);
	if (target_is_in_chan == -2 || target_is_in_chan == -1)
		return (send_message(ERR_NOTONCHANNEL(this->get_name(), current_user.get_nick(), chan_to_part->get_name()), current_pollfd), (NONE));
	
	// ici faire suprimer la cible du chanelle et envoyer le message
	ssize_t index_u = _get_index_of_userhuman_by_nick(current_user.get_nick());
	if (index_u == -1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user.get_nick()), current_pollfd), (NONE));
	
	ssize_t index_c = _get_index_channel_by_name(chan_to_part->get_name());
	if (index_c == -1)
		return (send_message(ERR_NOTONCHANNEL(this->get_name(), current_user.get_nick(), chan_to_part->get_name()), current_pollfd), (NONE));

	send_message(PART_MSG(current_user.get_nick(), current_user.get_name(), current_user.get_hostname(), chan_to_part->get_name(), current_cmd.get_message()), current_pollfd);
	_send_message_to_a_chanelle(current_user, *chan_to_part, PART_MSG(current_user.get_nick(), current_user.get_name(), current_user.get_hostname(), chan_to_part->get_name(), current_cmd.get_message()));
	chan_to_part->errase_user(static_cast<size_t>(index_u));
	current_user.errase_chan(static_cast<size_t>(index_c));
	return (NONE);
}
