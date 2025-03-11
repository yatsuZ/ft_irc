/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whowas.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:24:54 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/11 14:00:09 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* WHOWAS <nickname>
	Demande les informations d'un user qui n'existe plus dans le serveur.
*/
Reaction_Serv	Irssi_serv::ft_whowas(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::string	nick;
	std::vector<std::string> cmd_args = current_cmd.get_arg();
	if (cmd_args.size() > 0)
		nick = cmd_args[0];
	else
		nick = current_user->get_nick();
	std::cout << PINK <<  "-------- WHOIS -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	send_message(ERR_WASNOSUCHNICK(this->get_name(), current_user->get_nick(), nick), current_pollfd);
	send_message(RPL_ENDOFWHOWAS(this->get_name(), current_user->get_nick(), nick), current_pollfd);
	return (NONE);
}