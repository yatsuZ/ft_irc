/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:53:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:44:56 by yzaoui           ###   ########.fr       */
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
	(void)	index_of_current_pollfd;
	size_t i = 0;
	std::vector<std::string> c_args = current_cmd.get_arg();
	UserHuman * who = NULL; //utilisateur cible

	std::cout << PINK <<  "-------- WHOIS -----------" << NOCOLOR << std::endl;

	//check si parametre [nick] renseigné
	if (c_args.size() != 1)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->getNick(), current_cmd.get_cmd()), current_pollfd), (NONE));
	// if (c_args.size() > 1)
		//
	//recherche l'utilisateur
	while (i < _all_User.size())
	{
		if (_all_User[i].getNick() == c_args[0])
		{
			
			who = &_all_User[i];
			break;
		}
		i++;
	}	
	//cas utilisateur [nick] non trouvé
	if (who == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), current_user->getNick()), current_pollfd), (NONE));

	send_message(RPL_WHOISUSER(get_name(), get_name(), who->getNick(), who->getName(), who->get_ip_to_string(), who->getRealname()), current_pollfd);
	send_message(RPL_ENDOFWHOIS(this->get_name(), who->getNick()), current_pollfd);
	return (NONE);
}