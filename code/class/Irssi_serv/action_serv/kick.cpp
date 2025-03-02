/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:48:20 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/03 00:40:21 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_kick(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_user;
	(void)	current_pollfd;
	std::cout << "-------- KICK -----------" << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));
	// else if ()// VERIFIER QUIL EST PAS BANN // SAMIRA ici

	if (current_cmd.get_arg().size() < 2)
	{
		send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd);
		return (NONE);
	}
	Channel * current_chan = _get_channel_by_name(current_cmd.get_arg()[0]);
	if (current_chan == NULL)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), current_cmd.get_arg()[0]), current_pollfd), NONE);
	UserHuman * target_user = _get_userhuman_by_nick(current_cmd.get_arg()[1]);
	if (!target_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_cmd.get_arg()[1]), current_pollfd), (NONE));
	else if (target_user->get_nick() == current_user->get_nick())
		return (send_message(ERR_BADCHANMASK(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));

	int res = _is_op_in_chan(*current_user, *current_chan);
	int target_is_in_chan = _is_op_in_chan(*target_user, *current_chan);
	if (target_is_in_chan == -2 || target_is_in_chan == -1)
		return (send_message(ERR_USERNOTINCHANNEL(this->get_name(), current_user->get_nick(), target_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	else if (res == -1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick()), current_pollfd), (NONE));
	else if (res == -2)
		return (send_message(ERR_USERNOTINCHANNEL(this->get_name(), current_user->get_nick(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	else if (res == -3)
		return (send_message(ERR_CHANOPRIVSNEEDED(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));

	// ici faire suprimer la cible du chanelle et envoyer le message
	ssize_t index_u = _get_index_of_userhuman_by_nick(target_user->get_nick());
	if (index_u == -1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), target_user->get_nick()), current_pollfd), (NONE));

	ssize_t index_c = _get_index_channel_by_name(current_chan->get_name());
	if (index_c == -1)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), current_cmd.get_arg()[0]), current_pollfd), NONE);

	current_chan->errase_user(static_cast<size_t>(index_u));
	target_user->errase_chan(static_cast<size_t>(index_c));
	send_message(KICK_MSG_TARGET(current_chan->get_name(), target_user->get_nick(), current_cmd.get_message()), this->_all_pollfd[target_user->get_index_pollfd()]);
	std::vector<size_t> list_of_index_u = current_chan->get_index_users();
	for (size_t i = 0; i < list_of_index_u.size(); i++)
	{
		size_t curent_index_u = list_of_index_u[i];
		UserHuman & c_u(this->_all_User[curent_index_u]);
		send_message(KICK_MSG_OTHER(c_u.get_nick(), c_u.get_name(), c_u.get_hostname(), current_chan->get_name(), target_user->get_nick(), current_cmd.get_message()), this->_all_pollfd[c_u.get_index_pollfd()]);
	}
	return (NONE);
}
