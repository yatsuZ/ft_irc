/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:24:06 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/23 20:10:29 by smlamali         ###   ########.fr       */
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
	std::string	real_name;
	std::vector<std::string>	l_args = current_cmd.get_arg();

	std::cout << PINK << "-------- USER -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;
	if (current_user == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*", "*"), current_pollfd), (NONE));

	else if (l_args.size() < 4)
	{
		send_message(ERR_NEEDMOREPARAMS(current_cmd.get_cmd(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd);
		return (NONE);
	}
	// for (size_t i=0; i< l_args.size(); i++)
	// 	std::cout << " l_args[" << i << "] =" << l_args[i] << std::endl;
	
	if (current_user->get_Set_User())
		return (send_message(ERR_ALREADYREGISTRED(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
	
	real_name = l_args[3];

	if (real_name[0] == ':')
		real_name.erase(0,1);
	for (size_t i=4;i<l_args.size(); i++)
		real_name += " " + l_args[i];
	current_user->set_name(l_args[0]);	
	current_user->set_hostname(l_args[1]);
	current_user->set_servername(l_args[2]);
	current_user->set_Realname(real_name);

	send_message(RPL_USER(get_name(), current_user->get_nick(), current_user->get_name(), current_user->get_realname()), current_pollfd);
	current_user->get_welcolm(get_name(), current_cmd.get_action() ,current_pollfd);


	return (NONE);
}