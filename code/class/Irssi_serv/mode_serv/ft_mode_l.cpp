/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_l.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:12:18 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/07 18:00:32 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

// MODE [[+|-]l] [limite]
//	set une limite d'utilisateurs dans le channel

Mode	Irssi_serv::ft_mode_l(Cmd_irssi &cmd, UserHuman * human, pollfd &current_pollfd, Channel *chan)
{
	std::cout << YELLOW << "------ Mode l (limite)--------" << NOCOLOR << std::endl; 

	(void)human;
	(void)current_pollfd;
	(void)chan;
	std::vector<std::string> cmd_args = cmd.get_arg();
	if (cmd_args.empty())
		return (NO_MODE);

	if (cmd_args[1] == "+l")
		return (send_message(RPL_MODE_L(human->get_nick(), human->get_hostname(), 
			human->get_ip_to_string(), chan->get_name(), cmd_args[0], cmd_args[1]), current_pollfd), NO_MODE);
	if (cmd_args[1] == "-l")
		return (send_message(RPL_RMV_L(human->get_nick(), human->get_hostname(), 
			human->get_ip_to_string(), chan->get_name(), cmd_args[0]), current_pollfd), NO_MODE);

	return (NO_MODE);
}