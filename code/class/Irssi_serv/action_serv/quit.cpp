/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 12:53:49 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 18:27:31 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

// :<nickname>!<user>@<host> QUIT :<message>

Reaction_Serv	Irssi_serv::ft_quit(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << PINK <<  "-------- QUIT -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));

	std::string msg_of_leaving;
	std::vector<std::string> list_arg = current_cmd.get_arg();

	if (list_arg.empty())
		msg_of_leaving = "default message leaving";
	for (size_t i = 0; i < list_arg.size(); i++)
	{
		msg_of_leaving += (!i && list_arg[i][0] == ':') ? list_arg[i].substr(1) : list_arg[i];
		if (i)
			msg_of_leaving += list_arg[i];
	}
	
	std::string all_message = ":" + current_user->get_nick() + "!" + current_user->get_name() + "@" + this->get_name() + " " + current_cmd.get_cmd() + " :" + msg_of_leaving;
	send_message(all_message, current_pollfd);
	return (this->ft_disconnect(current_cmd, current_user, current_pollfd, index_of_current_pollfd));
}
