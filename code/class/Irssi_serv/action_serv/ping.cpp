/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:52 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 18:27:44 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_ping(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;
	bool	parametre_avec_espace = false;
	std::vector<std::string> list_args = current_cmd.get_arg();
	std::cout << PINK << "-------- PING -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	std::string usernick = this->_get_userhuman_by_index_of_pollfd(index_of_current_pollfd)->get_nick();

	if (list_args.empty() || list_args[0].empty())
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), usernick, current_cmd.get_cmd()), current_pollfd), (NONE));
	
	if (list_args[0] == ":")
		parametre_avec_espace = true;
	
	if (parametre_avec_espace && list_args.size() == 1)
		return (send_message(ERR_NOORIGIN(this->get_name(), usernick), current_pollfd), (NONE));

	std::string msg = "PONG ";

	for (size_t i = 0; i < list_args.size(); i++)
	{
		msg += list_args[i];
	}
	msg += CRLF;
	return (send_message(msg, current_pollfd), (NONE));
}
