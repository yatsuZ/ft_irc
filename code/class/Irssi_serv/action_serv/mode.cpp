/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/24 19:46:51 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/*
 MODE [nickname] {[+|-] | i | w | s | o} 
	Definit la maniere dont est percu l'utilisatuer par les autres
	> i: invisible
	> o: operator
 
 MODE [channel] {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [ban mask>]
 	>i: definir/supp canal sur invitation
 	>t: def/supp restriction TOPIC (pour op de cannaux)
 	>k: def/supp clé du canal (mdp)
 	>o: donner/retirer privilege de l'op de canal
 	>l: def/supp limite d'utilisateurs pour le canal
*/

// mode [target][mode][parametre] 
/*
cas 1	: /mode [target]					 <===>	/mode #lobby 	OU /mode user
cas 2 	: /mode [target][mode op]			 <===>	/mode #lobby +i OU /mode user -i 
cas 3 	: /mode [target][mode op][parametre] <===>	/mode #lobby +k secret
*/

/*	reponse de /mode [target]
	/mode channel => #lobby +tn 
*/
Reaction_Serv	Irssi_serv::ft_mode(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << "------------- MODE -------------" << std::endl;
	(void)index_of_current_pollfd;

	std::vector<std::string>	args = current_cmd.get_arg();
	if (args.empty())
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), NONE);

	Channel	*channel = _get_channel_by_name(args[0]);
	Channel	*human = _get_channel_by_name(args[0]);

	if (channel == NULL && human == NULL)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), args[0]), current_pollfd), NONE);
	if (channel != NULL)
	{
		if (args.size() == 1)
			return (send_message(RPL_CHANNELMODEIS(this->get_name(), current_user->get_nick(), channel->get_name(), ""),current_pollfd), NONE);
	}

	if (human != NULL)
	{
		if (args.size() == 1)
			return (send_message(RPL_UMODEIS(this->get_name(), current_user->get_nick(), ""), current_pollfd), NONE);
	}
	return (NONE);
}




// {
// 	std::vector<std::string> cmd_args = current_cmd.get_arg();
// 	UserHuman	*target_user = this->_get_userhuman_by_nick(cmd_args[0]);
// 	Channel	 	*target_chan = this-> _get_channel_by_name(cmd_args[0]);
// 	std::cout << PINK <<  "-------- MODE --------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;
// 	//USER MODE
// 	// if (cmd_args.size() <= 2) // dans lobby, client peut envoyer /mode #channel
// 	// 	return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), "MODE"), current_pollfd), (NONE));

// 	//si la cible n'est ni un user ni un chan connu
// 	if (target_user == NULL && target_chan == NULL)
// 		return (send_message(ERR_NOSUCHNICK(this->get_name(), cmd_args[0]), current_pollfd), NONE);

// 	//si la cible est un user
// 	if (target_user != NULL)
// 	{	
// 		if ((cmd_args[1] == "+i" && current_user->get_mode() != I) ||
// 			(cmd_args[1] == "-i" && current_user->get_mode() == I))
// 		{
// 			target_user->set_mode(I);
// 			return (send_message(":" + current_user->get_nick() + " MODE " + target_user->get_name() + " :" + cmd_args[1] + CRLF, current_pollfd), NONE);
// 		}
// 	}
// 	//max args MODE [chan][mod][target_user] || MODE [chan][mode] <= a faire apres class chan
		
// 	//CHANNEL MODE
// 	if (target_chan != NULL)
// 	{	
// 		//check le mode et renvoyer la fonction du mode correspondant
// 	}
// 	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
// }