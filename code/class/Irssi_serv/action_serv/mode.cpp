/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:46:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/09 20:01:27 by smlamali         ###   ########.fr       */
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
	(void)	index_of_current_pollfd;
	std::cout << PINK <<  "-------- MODE --------" << NOCOLOR << std::endl;

	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}
