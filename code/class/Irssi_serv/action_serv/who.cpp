/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 16:58:11 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/02 19:45:21 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/*----------- COMMAND: WHO [name]
	le client envoie une requete "who" pour recevoir du serveur en reponse
	une liste d'information sur le nom donné.

	Le serveur peut repondre avec zéro (RPL_ENDOFWHO), une ou 
	plusieurs réponses (RPL_WHOREPLY).

	name=channel name: liste touts les users dans le channel
	name=nickname : user retourné (?)
--------------- END*/

/*RPL WHO possibles
	<-/who
	->
*/
// Reaction_Serv	ft_who(Cmd_irssi &current_cmd, UserHuman *current_user, pollfd &current_pollfd, size_t & idx_current_pollfd)
// {
// 	(void)current_cmd;
// 	(void)current_user;
// 	(void)current_pollfd;
// 	(void)idx_current_pollfd;
//  	// std::cout << "-------------- WHO --------------" << stdS::endl;

//  	// std::vecteur<std::string> cmd_args = current_cmd.get_arg();

//  	// UserHuman	*user = _get_userhuman_by_nick(cmd_arg[0]);
// 	// Channel		*chan = _get_channel_by_name(cmd_arg[0]);

// 	// if (cmd_args.empty() == NULL)
		
// 	// if (user != NULL)
// 	// {
// 	// 	if (user->get_mode() != I)
// 	// 		//rpl who sur user
// 	// 	else
// 	// }
// 	return (NONE);
// }