/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/02 19:26:03 by smlamali         ###   ########.fr       */
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
cas 1	: /mode [target]					 <===>	/mode #lobby 	 /mode user
cas 2 	: /mode [target][mode op]			 <===>	/mode #lobby +i  /mode user -i 
cas 3 	: /mode [target][mode op][parametre] <===>	/mode #lobby +k secret
*/

Reaction_Serv	Irssi_serv::ft_mode(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::cout << "------------- MODE -------------" << std::endl;
	(void)index_of_current_pollfd;

	std::vector<std::string>	args = current_cmd.get_arg();

	Channel	*target_channel = _get_channel_by_name(args[0]);
	UserHuman	*target_user = _get_userhuman_by_nick(args[0]);

	//-----------UNKNOWN USER AND CHANNEL
	if (target_channel == NULL && target_user == NULL)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), args[0]), current_pollfd), NONE);
	
	//------------ CHANNEL MODE
	if (target_channel != NULL)
	{
		if (args.size() == 1) //ajouter list_mode
			return (send_message(RPL_CHANNELMODEIS(this->get_name(), current_user->get_nick(), target_channel->get_name(), target_channel->list_mode()),current_pollfd), NONE);
	}
	
	//----------------- USER MODE
	else if (target_user != NULL)
	{
		if (current_user->get_nick() != target_user->get_nick())
			return (send_message(ERR_USERSDONTMATCH(this->get_name(), current_user->get_nick()), current_pollfd), NONE);
		if (args.size() == 1) //ajouter user->liste_mode au lieu de ""
			return (send_message(RPL_UMODEIS(this->get_name(), current_user->get_nick(), target_user->list_mode()), current_pollfd), NONE);
	}

	return (NONE);
}


/* TO DO LIST
	>check /mode [target] <= voir si la liste de mode s'affiche correctement sur irssi
	>implementer toutes les de mode channel
*/