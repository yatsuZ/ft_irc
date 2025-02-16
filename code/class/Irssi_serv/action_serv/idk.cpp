/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:26:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:10:35 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_idk(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;
	(void)	index_of_current_pollfd;
	std::cout << YELLOW << "-------- I DONT KNOW ?? -----------" << NOCOLOR << std::endl;

	// std::cout << current_cmd << std::endl;
	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}
