/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/08 13:29:24 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/*
 MODE [nickname] {[+|-] | i} 
	Definit la maniere dont est percu l'utilisatuer par les autres
	> i: invisible
	> o: operator
 
 MODE [#channel] {[+|-] | i | t | k | o | l} [parametre]
 	>i: definir/supp canal sur invitation
 	>t: def/supp restriction TOPIC (pour op de cannaux)
 	>k: def/supp clé du canal (mdp)
 	>o: donner/retirer privilege de l'op de canal
 	>l: def/supp limite d'utilisateurs pour le canal
*/

// MODE [target][mode][parametre] 
/*
cas 1	: /mode [target]					 <===>	/mode #lobby 	 /mode user
cas 2 	: /mode [target][mode op]			 <===>	/mode #lobby +i  /mode user -i 
cas 3 	: /mode [target][mode op][parametre] <===>	/mode #lobby +k secret
*/

Reaction_Serv	Irssi_serv::ft_mode(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)index_of_current_pollfd;
	std::cout << PINK <<  "-------- MODE --------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	std::vector<std::string>	args = current_cmd.get_arg();

	Channel	*target_channel = _get_channel_by_name(args[0]);
	UserHuman	*target_user = _get_userhuman_by_nick(args[0]);

	if (args.empty())
		return (NONE);

	//-----------UNKNOWN USER AND CHANNEL
	if (target_channel == NULL && target_user == NULL)
		return (send_message(ERR_NOSUCHCHANNEL(this->get_name(), current_user->get_nick(), args[0]), current_pollfd), NONE);
	
	//------------ CHANNEL MODE
	if (target_channel != NULL)
	{
		if (args.size() == 1) //ajouter list_mode
			return (send_message(RPL_CHANNELMODEIS(this->get_name(), current_user->get_nick(), target_channel->get_name(), target_channel->list_mode()),current_pollfd), NONE);
		if (!target_channel->is_operator(_get_index_of_userhuman_by_nick(current_user->get_nick())))
			return(send_message(ERR_CHANOPRIVSNEEDED(this->get_name(), current_user->get_nick(), target_channel->get_name()), current_pollfd), NONE);
		do_mode(current_cmd, current_user, current_pollfd, target_channel);
	}
	
	//----------------- USER MODE
	else if (target_user != NULL)
	{
		if (args.size() == 1)
			return (send_message(RPL_UMODEIS(this->get_name(), current_user->get_nick(), target_user->list_mode()), current_pollfd), NONE);
		if (current_user->get_nick() != target_user->get_nick())
			return (send_message(ERR_USERSDONTMATCH(this->get_name(), current_user->get_nick()), current_pollfd), NONE);
		do_mode(current_cmd, current_user, current_pollfd, NULL);
	}

	return (NONE);
}


/* TO DO LIST
	>check /mode [target] <= voir si la liste de mode s'affiche correctement sur irssi
	>implementer toutes les de mode channel
*/