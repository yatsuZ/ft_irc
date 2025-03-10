/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:53:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/10 18:33:01 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* WHOIS [<target>] [nick]
	renvoi les infos d'un user (nick username host * :realname )
	[<target>]	: envoie la requete à un serveur [<target>] (/!\ pas à faire /!\)
	[nick]		: utilisateur cible dont on veut les infos
*/

Reaction_Serv	Irssi_serv::ft_whois(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::vector<std::string> cmd_args = current_cmd.get_arg();
	UserHuman * target_human = NULL; //utilisateur cible

	std::cout << PINK <<  "-------- WHOIS -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	//si pas d'arguments, target = current_user
	if (cmd_args.size() == 0)
		target_human = current_user;
	else
		target_human = _get_userhuman_by_nick(cmd_args[0]);

	if (target_human == NULL)
	{
		send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick(), cmd_args[0]), current_pollfd);
		return (send_message(ERR_WASNOSUCHNICK(this->get_name(), current_user->get_nick(), cmd_args[0]), current_pollfd), NONE);
	}
	send_message(RPL_WHOISUSER(this->get_name(), current_user->get_nick(), target_human->get_nick(), target_human->get_name(), 
		target_human->get_ip_to_string(), target_human->get_realname()), current_pollfd);
	send_message(RPL_WHOISACTUALLY(this->get_name(), current_user->get_nick(), target_human->get_nick(), 
		target_human->get_hostname(), target_human->get_ip_to_string()), current_pollfd);
	send_message(RPL_WHOISSERVER(this->get_name(), current_user->get_nick(), target_human->get_nick()), current_pollfd);
	send_message(RPL_ENDOFWHOIS(this->get_name(), current_user->get_nick(), target_human->get_nick()), current_pollfd);
	return (NONE);
}

/*
	//check si parametre [nick] renseigné
	if (c_args.size() != 1)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), (NONE));

	//recherche l'utilisateur
	while (i < _all_User.size())
	{
		if (_all_User[i].get_nick() == c_args[0])
		{	
			who = &_all_User[i];
			break;
		}
		i++;
	}	
	//cas utilisateur [nick] non trouvé
	if (who == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user->get_nick()), current_pollfd), (NONE));

	send_message(RPL_WHOISUSER(get_name(), get_name(), who->get_nick(), who->get_name(), who->get_ip_to_string(), who->get_realname()), current_pollfd);
	send_message(RPL_ENDOFWHOIS(this->get_name(), who->get_nick()), current_pollfd);*/