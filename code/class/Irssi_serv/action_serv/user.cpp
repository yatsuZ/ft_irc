/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:24:06 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/06 20:13:18 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"
/* --- USER [username] [hostname] [servername] [realname]
	Permet d'identifier l'utilisateur aupres du serveur au moment de la connexion
	Ne peut pas etre reutiliser deux fois 
	[username]

*/
Reaction_Serv	Irssi_serv::ft_user(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;

	std::string	realname;

	std::vector<std::string> l_args = current_cmd.get_arg();
	User *					 human = _get_userhuman_by_index_of_pollfd(index_of_current_pollfd);
	
	std::cout << PINK << "-------- USER -----------" << NOCOLOR << std::endl;

	if (l_args.size() < 4)
	{
		send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd()), current_pollfd);
		return (NONE);
	}
	// TO DO : check si user deja enregistré (ERR_ALREADYREGISTERED)
	
	realname = l_args[3];

	if (realname[0] == ':')
		realname.erase(0,1);
	for (size_t i=4;i<l_args.size(); i++)
		realname += " " + l_args[i];
	human->setName(l_args[0]);
	human->setHostname(l_args[1]);
	human->setServername(l_args[2]);
	human->setRealname(realname);

	send_message(RPL_USER(get_name(), human->getNick(), human->getName(), human->getRealname()), current_pollfd);

	return (NONE);
}