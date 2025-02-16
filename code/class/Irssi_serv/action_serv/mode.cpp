/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 13:44:41 by yzaoui           ###   ########.fr       */
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
	(void)	index_of_current_pollfd;
	std::vector<std::string> cmd_args = current_cmd.get_arg();
	UserHuman *target = this->_get_userhuman_by_nick(cmd_args[0]);

	std::cout << PINK <<  "-------- MODE --------" << NOCOLOR << std::endl;
	//USER MODE
	if (cmd_args.size() <= 1)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->getNick(), "MODE"), current_pollfd), (NONE));

	if (target == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), cmd_args[0]), current_pollfd), NONE);

	if ((cmd_args[1] == "+i" && !current_user->getMode()) ||
		(cmd_args[1] == "-i" && current_user->getMode()))
	{
		target->setMode();
		return (send_message(":" + current_user->getNick() + " MODE " + target->getName() + " :" + cmd_args[1] + CRLF, current_pollfd), NONE);
	}
	//max args MODE [chan][mod][target] || MODE [chan][mode] <= a faire apres class chan
	//check nickname puis si arg[1] == mode valide/connu
	//appliquer le mode
		
	//CHANNEL MODE

	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}