/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:48:20 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/02 18:24:15 by yzaoui           ###   ########.fr       */
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

	int res = _is_op_in_chan(*current_user, *current_chan);
	int target_is_in_chan = _is_op_in_chan(*target_user, *current_chan);
	if (target_is_in_chan == -2 || target_is_in_chan == -1)
		return (send_message(ERR_USERNOTINCHANNEL(this->get_name(), current_user->get_nick(), target_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	if (res == -1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick()), current_pollfd), (NONE));
	if (res == -2)
		return (send_message(ERR_USERNOTINCHANNEL(this->get_name(), current_user->get_nick(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));
	if (res == -3)
		return (send_message(ERR_CHANOPRIVSNEEDED(this->get_name(), current_user->get_nick(), current_chan->get_name()), current_pollfd), (NONE));

	// ici faire suprimer la cible du chanelle et envoyer le message
	

	return (NONE);
}
