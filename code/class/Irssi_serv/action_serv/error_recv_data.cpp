/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_recv_data.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:21:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/03 13:24:25 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_error_recv_data(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	index_of_current_pollfd;
	std::cout << "-------- ERROR OF FUNCTION RECV -----------" << std::endl;

	this->send_message(std::string(getColorCode(RED)) + "Error de recv data Fail..." + std::string(getColorCode(NOCOLOR)), current_pollfd);
	return (NONE);
}

