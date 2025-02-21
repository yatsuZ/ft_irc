/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/21 19:41:42 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/*
 MODE [nickname] {[+|-] | i | w | s | o} 
	Definit la maniere dont est percu l'utilisatuer par les autres
	> i: invisible
	> o: operator
*/

/* 
 MODE [channel] {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [ban mask>]
 	>i: definir/supp canal sur invitation
 	>t: def/supp restriction TOPIC (pour op de cannaux)
 	>k: def/supp clé du canal (mdp)
 	>o: donner/retirer privilege de l'op de canal
 	>l: def/supp limite d'utilisateurs pour le canal
*/

Reaction_Serv	Irssi_serv::ft_mode(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::vector<std::string> cmd_args = current_cmd.get_arg();
	UserHuman	*target_user = this->_get_userhuman_by_nick(cmd_args[0]);
	Channel	 	*target_chan = this-> _get_channel_by_name(cmd_args[0]);
	std::cout << PINK <<  "-------- MODE --------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;
	//USER MODE
	if (cmd_args.size() <= 1)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), "MODE"), current_pollfd), (NONE));

	//si la cible n'est ni un user ni un chan connu
	if (target_user == NULL && target_chan == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), cmd_args[0]), current_pollfd), NONE);

	//si la cible est un user
	if (target_user != NULL)
	{	
		if ((cmd_args[1] == "+i" && !current_user->getMode()) ||
			(cmd_args[1] == "-i" && current_user->getMode()))
		{
			target_user->set_mode();
			return (send_message(":" + current_user->get_nick() + " MODE " + target_user->get_name() + " :" + cmd_args[1] + CRLF, current_pollfd), NONE);
		}
	}
	//max args MODE [chan][mod][target_user] || MODE [chan][mode] <= a faire apres class chan
		
	//CHANNEL MODE
	// if (target_chan != NULL)
	// {
	// 	//check le mode et renvoyer la fonction du mode correspondant
	// 	//essayer de faire a la methode de yaya (tableau de fct)
	// }
	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}