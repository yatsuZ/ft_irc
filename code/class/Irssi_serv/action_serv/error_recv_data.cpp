/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_recv_data.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:21:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/27 15:48:07 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_error_recv_data(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_user;
	std::cout << "-------- ERROR OF FUNCTION RECV -----------" << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	send_message(RED + "Error de recv data Fail... / or / Invalide char...." + NOCOLOR + CRLF, current_pollfd);
	return (NONE);
}

