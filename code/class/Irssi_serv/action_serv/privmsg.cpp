/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:20:33 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/27 19:59:34 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

// message envoyer : :<nick>!~<username>@<hostname> PRIVMSG <CIBLE> :<msg>
// message recu    : PRIVMSG <cible> :<msg>

Reaction_Serv	Irssi_serv::ft_privmsg(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;
	std::cout << YELLOW << "-------- PRIVMSG -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	// 1. verifier si le user existe ou est ban
	if (!current_user)
		return (send_message(ERR_NOSUCHNICK(this->get_name(), "*"), current_pollfd), (NONE));
	// else if ()// VERIFIER QUIL EST PAS BANN // SAMIRA ici

// veirifer la argument vervier qu'il en as pas trop ni pas assez

// verifier si sa commence par un @ pour les ops
// recuper la cible verivier si cest un user ou chanelle (commence par un #) si il le trouve pas ou que le user nest pas dans le chanelle

	// 2.  ERR_CANNOTSENDTOCHAN  si il ne trouve pas le chanelle ou quil est pas dans le chanelle

	// 3. si cest @target alors envoye un message seulement aux opereteur
	// 4. envoye le message
	// std::cout << current_cmd << std::endl;
	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}
