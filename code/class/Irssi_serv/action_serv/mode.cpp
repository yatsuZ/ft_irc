/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/13 13:27:44 by smlamali         ###   ########.fr       */
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

Reaction_Serv	Irssi_serv::ft_mode(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	// (void)	current_cmd;
	// (void)	current_pollfd;
	(void)	index_of_current_pollfd;
	
	std::cout << PINK <<  "-------- MODE --------" << NOCOLOR << std::endl;
	size_t i = 0;
	std::vector<std::string> cmd_args = current_cmd.get_arg();
	UserHuman *current_user = _get_userhuman_by_index_of_pollfd(index_of_current_pollfd);
	UserHuman *target = NULL;
	//USER MODE
	if (cmd_args.size() <= 1)
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->getNick(), "MODE"), current_pollfd), (NONE));

	//check si nick existe (TO DO: creer fonction getUserByNick pour alleger le code)
	if (cmd_args.size() > 2)
	{
		while (i < _all_User.size())
		{
			if (_all_User[i].getNick() == cmd_args[0])
			{
				
				target = &_all_User[i];
				break;
			}
			i++;
		}	
	}

	if (target == NULL)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), cmd_args[0]), current_pollfd), NONE);

	if ((cmd_args[1] == "+i" && !current_user->getMode()) ||
		(cmd_args[1] == "-i" && current_user->getMode()))
	{
		target->setMode();
		return (send_message(":" + current_user->getNick() + " MODE " + cmd_args[0] + " :" + cmd_args[1] + CRLF, current_pollfd), NONE);
	}
	//max args MODE [chan][mod][target] || MODE [chan][mode] <= a faire apres class chan
	//check nickname puis si arg[1] == mode valide/connu
	//appliquer le mode
		
	//CHANNEL MODE

	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}