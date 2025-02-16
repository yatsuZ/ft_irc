/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_action.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:21:09 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:10:49 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_no_action(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_user;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << "-------- NO ACTION -----------" << std::endl;

	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}
