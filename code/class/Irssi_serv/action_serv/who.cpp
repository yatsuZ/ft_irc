/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:11 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/09 17:24:50 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/*----------- COMMAND: WHO [name]
	le client envoie une requete "who" pour recevoir du serveur en reponse
	une liste d'information sur le nom donné.

	Le serveur peut repondre avec zéro (RPL_ENDOFWHO), une ou 
	plusieurs réponses (RPL_WHOREPLY).

	name=channel name: liste touts les users dans le channel
	name=nickname : user retourné (?)
--------------- END*/
/*
	 RPL_WHOREPLY : :server 352 Nick * ~hostname ip server target_nick Away_status hopcount realname
	 Away_status => H (here) | G (gone)
	 hopcount: nombre de serveurs entre le client et celui ciblé par la requete (ici ":0")
*/

Reaction_Serv	Irssi_serv::ft_who(Cmd_irssi &current_cmd, UserHuman *current_user, pollfd &current_pollfd, size_t & idx_current_pollfd)
{
	(void)idx_current_pollfd;
 	std::cout << "-------------- WHO --------------" << std::endl;

	std::vector<size_t> list_user;
 	std::vector<std::string> cmd_args = current_cmd.get_arg();

 	UserHuman	chan_user;
 	UserHuman	*user = _get_userhuman_by_nick(cmd_args[0]);
	Channel		*chan = _get_channel_by_name(cmd_args[0]);

	if (user != NULL)
	{
		if (user->get_mode() != I)
		{
			send_message(RPL_WHOREPLY(this->get_name(), current_user->get_nick(), 
				"*", user->get_hostname(), user->get_ip_to_string(), user->get_nick(), 
				user->get_realname()), current_pollfd);
			return (send_message(RPL_ENDOFWHO(this->get_name(), current_user->get_nick(), user->get_nick()), current_pollfd), NONE);
		}
		if (user->get_mode() == I)
			return (send_message(RPL_ENDOFWHO(this->get_name(), current_user->get_nick(), user->get_nick()), current_pollfd), NONE);
	}

	if (chan != NULL)
	{
		std::cout << YELLOW << "WHO " << chan->get_name() << NOCOLOR << std::endl;
		//TO_DO : cas "WHO #lobby" verifier si user est dans lobby
		list_user = chan->get_index_users();
		std::cout << YELLOW << "nbrs of users in chan = " << list_user.size() << std::endl;
		if (list_user.empty())
			return (send_message(RPL_ENDOFWHO(this->get_name(), current_user->get_nick(), chan_user.get_nick()), current_pollfd), NONE);
		for (size_t i=0; i<list_user.size(); i++)
		{
			chan_user = this->_all_User[list_user[i]];
			std::cout << "user who => " << chan_user.get_nick() << std::endl;
			send_message(RPL_WHOREPLY(this->get_name(), current_user->get_nick(), 
			"*", chan_user.get_hostname(), chan_user.get_ip_to_string(), chan_user.get_nick(), 
			chan_user.get_realname()), current_pollfd);
			return (send_message(RPL_ENDOFWHO(this->get_name(), current_user->get_nick(), chan_user.get_nick()), current_pollfd), NONE);
		}
	}

	send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_name(), cmd_args[0]), current_pollfd);
	return (NONE);
}