/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_none.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:21:03 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/07 17:06:33 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Mode	Irssi_serv::ft_mode_none(Cmd_irssi &cmd, UserHuman * human, pollfd &current_pollfd, Channel *chan)
{
	(void)chan;
	(void)human;
	std::string	mode;

	if (cmd.get_arg().size() == 1)
		mode = cmd.get_arg()[0];
	if (cmd.get_arg().size() > 1)
		mode = cmd.get_arg()[1];
	
	std::cout << YELLOW << "------ UNKNOWN MODE " << mode << " ------" << NOCOLOR << std::endl; 
	return (send_message(ERR_UNKNOWNMODE(this->get_name(), human->get_nick(), mode), current_pollfd), NO_MODE);
}