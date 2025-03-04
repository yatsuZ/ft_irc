/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:49:06 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/05 00:21:14 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

// Si le canal est en mode +i (invité seulement) → Il faut être opérateur pour inviter quelqu'un.

Reaction_Serv	Irssi_serv::ft_invite(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;

	std::cout << "-------- INVITE -----------" << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

// parsser la cmd
	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));

	if (current_cmd.get_arg().size() < 2 || current_cmd.get_arg()[0][0] == ':' || current_cmd.get_arg()[1][0] == ':')
		return (send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), (NONE));

	Channel * current_chan = _get_channel_by_name(current_cmd.get_arg()[1]);
	if (current_chan == NULL)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), current_cmd.get_arg()[0]), current_pollfd), NONE);
	int res = _is_op_in_chan(*current_user, *current_chan);
	if (res == -1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick()), current_pollfd), (NONE));
	else if (res == -2)
		return (send_message(ERR_USERNOTINCHANNEL(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	// else if (res == -3)// ici verifier que le chanelle est en mode +i ou non
	// 	return (send_message(ERR_CHANOPRIVSNEEDED(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	// else if ()// VERIFIER QUIL EST PAS BANN // SAMIRA ici

	UserHuman * target_user = _get_userhuman_by_nick(current_cmd.get_arg()[0]);
	if (!target_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_cmd.get_arg()[0]), current_pollfd), (NONE));
	res = _is_op_in_chan(*target_user, *current_chan);
	std::cout << *target_user << std::endl << *current_chan << std::endl << this->_all_Channel << std::endl << this->_all_User << std::endl << "res = " << res << std::endl;
	if (res != -2)
		return (send_message(ERR_USERONCHANNEL(this->get_name(), target_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	// si la target est ban on envoye rien

	send_message(RPL_INVITING(this->get_name(), current_user->get_nick(), target_user->get_nick(), current_chan->get_name()), current_pollfd);
	send_message(INVIT_MSG_TARGET(current_user->get_nick(), current_user->get_name(), current_user->get_hostname(), target_user->get_nick(), current_chan->get_name()), _all_pollfd[target_user->get_index_pollfd()]);
	return (NONE);
}
