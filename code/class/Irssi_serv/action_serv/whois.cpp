/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:53:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/09 19:44:01 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* WHOIS [<target>] [nick]
	renvoi les infos d'un user (nick username host * :realname )
	[<target>]	: envoie la requete à un serveur cible (/!\ pas à faire /!\)
	[nick]		: utilisateur cible dont on veut les infos
*/

Reaction_Serv	Irssi_serv::ft_whois(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)current_pollfd;
	std::cout << PINK <<  "-------- WHOIS -----------" << NOCOLOR << std::endl;

	size_t i = 0;
	std::vector<std::string> c_args = current_cmd.get_arg();
	UserHuman * current_user = _get_userhuman_by_index_of_pollfd(index_of_current_pollfd);
	UserHuman * who; //utilisateur cible

	//check si parametre [nick] renseigné
	if (c_args.size() != 1)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->getNick(), current_cmd.get_cmd()), current_pollfd), (NONE));

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
	if (i == _all_User.size() - 1)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), c_args[0]), current_pollfd), (NONE));

	return (send_message(RPL_WHOISUSER(get_name(), who->getNick(), who->getName(), who->getHostname(), who->getRealname()), current_pollfd), (NONE));
}