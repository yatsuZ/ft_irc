/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_o.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:46:52 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/06 18:02:02 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"
/* MODE [#chanel][mode][target]*/

Mode	Irssi_serv::ft_mode_o(Cmd_irssi &current_cmd,  UserHuman *current_user, pollfd &current_pollfd, Channel *chan)
{
	std::vector<std::string> cmd_args = current_cmd.get_arg();
	if (cmd_args.size() != 2)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_name(), "MODE"), current_pollfd), NO_MODE);

	std::cout << YELLOW << "------ Mode o (operator)" << NOCOLOR << std::endl; 

	std::string target_nick = cmd_args[2];
	UserHuman 	*target_human = _get_userhuman_by_nick(target_nick);

	if (target_human == NULL)
	{
		send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick()),current_pollfd);
		//err441
		return NO_MODE;
	}
	if (cmd_args[1] == "+t")
	{
		chan->set_mode(T);
		return (send_message(RPL_MODE_O(current_user->get_nick(), current_user->get_hostname(), 
			current_user->get_ip_to_string(), chan->get_name(), cmd_args[1], target_nick), current_pollfd), NO_MODE);
	}
	else if (cmd_args[1] == "-t")
	{
		chan->erase_mode(T);
		return (send_message(RPL_MODE_O(current_user->get_nick(), current_user->get_hostname(), 
			current_user->get_ip_to_string(), chan->get_name(), cmd_args[1], target_nick), current_pollfd), NO_MODE);
	}
	return (send_message(ERR_UNKNOWNMODE(this->get_name(), current_user->get_nick(), cmd_args[1]), current_pollfd), NO_MODE);

}
