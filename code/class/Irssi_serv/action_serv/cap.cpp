/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:23:07 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 18:31:20 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/*
//commande otpionelle
Reaction_Serv	Irssi_serv::ft_cap(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << PINK << "-------- CAPACITI -----------" << NOCOLOR << std::endl;

	std::string msg;

	msg += ":serveur ";
	msg += current_cmd.get_cmd();// ou // msg += Fonctionalite_du_serveur_tab[CAP];
	msg += " * ";
	std::vector<std::string> list_dargument = current_cmd.get_arg();
	if (list_dargument.size() == 1 && list_dargument[0] == "LS")
	{
		msg += "LS :";
		// for (size_t i = 0; i < size_t(NBR_DE_FONCTIONALITE_DU_SERV); i++)
		// {
		// 	if (i != 0)
		// 		msg += " ";
		// 	msg += Fonctionalite_du_serveur_tab[i];
		// }
		msg += "\r\n";
		send_message(msg, current_pollfd);
	}

	return (NONE);
}
*/

//commande otpionelle
Reaction_Serv	Irssi_serv::ft_cap(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;

	std::cout << PINK << "-------- CAPABILITY -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));

}
