/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_recv_data.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:21:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:10:32 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_error_recv_data(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_user;
	(void)	index_of_current_pollfd;
	std::cout << "-------- ERROR OF FUNCTION RECV -----------" << std::endl;

	send_message(std::string(getColorCode(RED)) + "Error de recv data Fail..." + std::string(getColorCode(NOCOLOR)), current_pollfd);
	return (NONE);
}

