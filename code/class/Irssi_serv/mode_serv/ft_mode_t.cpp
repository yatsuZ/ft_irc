/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_t.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:09:54 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/06 16:34:01 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* /MODE [target] [+-t]
	definit si la commande TOPIC peut etre utilisé par des non operaturs ou non
*/

Mode	Irssi_serv::ft_mode_t(Cmd_irssi &current_cmd,  UserHuman *current_user, pollfd &current_pollfd, Channel *chan)
{
	std::cout << YELLOW << "------ Mode t (topic)" << NOCOLOR << std::endl; 

	std::vector<std::string> cmd_args = current_cmd.get_arg();

	if (cmd_args.size() != 2)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_name(), "MODE"), current_pollfd), NO_MODE);
	if (cmd_args[1] == "+t")
	{
		chan->set_mode(T);
		return (send_message(RPL_MODE_T(current_user->get_nick(), current_user->get_hostname(), 
			current_user->get_ip_to_string(), chan->get_name(), cmd_args[1]), current_pollfd), NO_MODE);
	}
	else if (cmd_args[1] == "-t")
	{
		chan->erase_mode(T);
		return (send_message(RPL_MODE_T(current_user->get_nick(), current_user->get_hostname(), 
			current_user->get_ip_to_string(), chan->get_name(), cmd_args[1]), current_pollfd), NO_MODE);
	}
	return (send_message(ERR_UNKNOWNMODE(this->get_name(), current_user->get_nick(), cmd_args[1]), current_pollfd), NO_MODE);
}