/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:24:06 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/09 17:25:30 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"
/* --- USER [username] [hostname] [servername] [real_name]
	Permet d'identifier l'utilisateur aupres du serveur au moment de la connexion
	Ne peut pas etre reutiliser deux fois 
	[username]

*/
Reaction_Serv	Irssi_serv::ft_user(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << PINK << "-------- USER -----------" << NOCOLOR << std::endl;

	std::string	real_name;
	std::vector<std::string>	l_args = current_cmd.get_arg();
	UserHuman *					human = _get_userhuman_by_index_of_pollfd(index_of_current_pollfd);
	std::string nick;
	if (human == NULL)
		nick= "*";
	else
		nick = human->getNick();

	if (human == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), nick), current_pollfd), (NONE));
	else if (l_args.size() < 4)
	{
		send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), nick, current_cmd.get_cmd()), current_pollfd);
		return (NONE);
	}

	if (human->getSet_User())
		return (send_message(ERR_ALREADYREGISTRED(current_cmd.get_cmd()), current_pollfd), (NONE));
	
	real_name = l_args[3];

	if (real_name[0] == ':')
		real_name.erase(0,1);
	for (size_t i=4;i<l_args.size(); i++)
		real_name += " " + l_args[i];
	human->setName(l_args[0]);
	human->setHostname(l_args[1]);
	human->setServername(l_args[2]);
	human->setRealname(real_name);

	send_message(RPL_USER(get_name(), human->getNick(), human->getName(), human->getRealname()), current_pollfd);
	send_message(RPL_WELCOME(this->get_name(), human->getNick(), human->getName(), human->get_ip_to_string()), current_pollfd);
	send_message(RPL_YOURHOST(this->get_name(), human->getNick(), "<" + CYAN + "Yassine" + PINK + "Samira " + YELLOW +"Comme"+NOCOLOR+"> 0.1"), current_pollfd);

	human->setting_User();

	return (NONE);
}