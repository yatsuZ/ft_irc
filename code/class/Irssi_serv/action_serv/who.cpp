/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:11 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/07 15:38:24 by smlamali         ###   ########.fr       */
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
	// (void)current_cmd;
	// (void)current_user;
	// (void)current_pollfd;
	(void)idx_current_pollfd;
 	std::cout << "-------------- WHO --------------" << std::endl;

 	std::vector<std::string> cmd_args = current_cmd.get_arg();

 	UserHuman	*user = _get_userhuman_by_nick(cmd_args[0]);
	Channel		*chan = _get_channel_by_name(cmd_args[0]);

	if (cmd_args.empty())
		return NONE;

	if (user != NULL)
	{
		if (user->get_mode() != I)
		{
			send_message(RPL_WHOREPLY(this->get_name(), current_user->get_nick(), 
				"*", user->get_hostname(), user->get_ip_to_string(), user->get_nick(), 
				user->get_realname()), current_pollfd);
			return (send_message(RPL_ENDOFWHO(this->get_name(), current_user->get_nick(), user->get_nick()), current_pollfd), NONE);
		}
	}

	if (chan != NULL)
	{
		//boucler who_reply sur chaque user dans channel
		send_message(RPL_WHOREPLY(this->get_name(), current_user->get_nick(), 
				"*", user->get_hostname(), user->get_ip_to_string(), user->get_nick(), 
				user->get_realname()), current_pollfd);
			return (send_message(RPL_ENDOFWHO(this->get_name(), current_user->get_nick(), user->get_nick()), current_pollfd), NONE);
	}
	return (NONE);
}