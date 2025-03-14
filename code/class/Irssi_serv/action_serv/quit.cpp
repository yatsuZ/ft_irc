/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:53:49 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/11 13:57:45 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

// :<nickname>!<user>@<host> QUIT :<message>

Reaction_Serv	Irssi_serv::ft_quit(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << PINK <<  "-------- QUIT -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*", "*"), current_pollfd), (NONE));

	std::string msg_of_leaving;
	std::vector<std::string> list_arg = current_cmd.get_arg();

	if (list_arg.empty())
		msg_of_leaving = current_user->get_msg_leave();
	for (size_t i = 0; i < list_arg.size(); i++)
	{
		msg_of_leaving += (!i && list_arg[i][0] == ':') ? list_arg[i].substr(1) : list_arg[i];
		if (i)
			msg_of_leaving += list_arg[i];
	}

	msg_of_leaving = "Quit: " + msg_of_leaving;

	this->_send_message_to_a_all_chanelle(*current_user, OTHER_QUIT_MSG(current_user->get_nick(), current_user->get_name(), current_user->get_hostname(), msg_of_leaving));
	send_message(SELF_QUIT_MSG(msg_of_leaving), current_pollfd);
	return (this->ft_disconnect(current_cmd, current_user, current_pollfd, index_of_current_pollfd));
}