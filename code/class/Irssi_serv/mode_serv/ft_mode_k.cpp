/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_k.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:26:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/07 17:56:27 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* MODE #channel [[+|-]k] [keyword]
	permet de set une clé au channel
*/
Mode	Irssi_serv::ft_mode_k(Cmd_irssi &cmd, UserHuman * user, pollfd &current_pollfd, Channel *chan)
{
	std::cout << YELLOW << "------ Mode k (key)--------" << NOCOLOR << std::endl; 
	std::vector<std::string> cmd_args = cmd.get_arg();

	if (cmd_args.size() != 3)
		return (NO_MODE);

	if (cmd_args[1] == "+k")
		chan->set_key(cmd_args[2]);	
	else if (cmd_args[1] == "-k")
		chan->set_key("");

	return (send_message(RPL_MODE_K(user->get_nick(), user->get_hostname(), user->get_ip_to_string(), 
			chan->get_name(), cmd_args[1], cmd_args[2]), current_pollfd), NO_MODE);
}