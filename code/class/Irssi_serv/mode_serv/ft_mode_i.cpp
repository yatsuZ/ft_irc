/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_i.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:18:44 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/05 19:50:25 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* ----/MODE [target] [[<+/->]i]
	target = user <= rend l'user invisible
	target = channel <= rend le channel accessible sur invite uniquement
*/

Mode	Irssi_serv::ft_mode_i(Cmd_irssi &current_cmd,  UserHuman *current_user, pollfd &current_pollfd, Channel *chan)
{
	std::cout << "------ Mode i (invite/invisile)" << std::endl; 

	std::vector<std::string> cmd_args = current_cmd.get_arg();
	std::string	mode = cmd_args[1];
	UserHuman	*target_user = _get_userhuman_by_nick(cmd_args[0]);
	
	if (chan != NULL)
	{
		if (mode == "+i" || mode == "i")
			chan->set_mode(I);
		else if (mode == "-i")
			chan->erase_mode(I);
		return (send_message(RPL_CHANONINVITE(current_user->get_nick(), current_user->get_hostname(), current_user->get_ip_to_string(), chan->get_name(), mode), current_pollfd), I);
	}

	if (target_user != NULL)
	{
		if (target_user->get_nick() != current_user->get_nick())
			return (send_message(ERR_USERSDONTMATCH(this->get_name(), current_user->get_nick()), current_pollfd), NO_MODE);
		target_user->set_mode(I); 
		return (send_message(RPL_INVISIBLE(current_user->get_nick(), cmd_args[0], cmd_args[1]), current_pollfd), I);
	}
	return (NO_MODE);
}