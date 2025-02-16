/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:24:06 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:44:21 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"
/* --- USER [username] [hostname] [servername] [real_name]
	Permet d'identifier l'utilisateur aupres du serveur au moment de la connexion
	Ne peut pas etre reutiliser deux fois 
	[username]

*/
Reaction_Serv	Irssi_serv::ft_user(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	index_of_current_pollfd;
	std::string	real_name;
	std::vector<std::string>	l_args = current_cmd.get_arg();

	std::cout << PINK << "-------- USER -----------" << NOCOLOR << std::endl;

	if (current_user == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));
	else if (l_args.size() < 4)
	{
		send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->getNick(), current_cmd.get_cmd()), current_pollfd);
		return (NONE);
	}

	if (current_user->getSet_User())
		return (send_message(ERR_ALREADYREGISTRED(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
	
	real_name = l_args[3];

	if (real_name[0] == ':')
		real_name.erase(0,1);
	for (size_t i=4;i<l_args.size(); i++)
		real_name += " " + l_args[i];
	current_user->setName(l_args[0]);	
	current_user->setHostname(l_args[1]);
	current_user->setServername(l_args[2]);
	current_user->setRealname(real_name);

	send_message(RPL_USER(get_name(), current_user->getNick(), current_user->getName(), current_user->getRealname()), current_pollfd);
	current_user->get_welcolm(get_name(), current_cmd.get_action() ,current_pollfd);


	return (NONE);
}