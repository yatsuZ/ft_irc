/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:48:54 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/12 01:17:50 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/// @brief Dans le protocole IRC, \x01 est utilisé pour délimiter les commandes spéciales appelées CTCP (Client-To-Client Protocol). donc on verifie sa 
/// @param cmd ma strucutre de commande que jai recu
/// @return vrai si commence et termine par le char \x01
bool Irssi_serv::_is_CTCP(Cmd_irssi & cmd)
{
	std::string msg = cmd.get_message();

	return msg.size() > 1 && msg[0] == '\x01' && msg[msg.size() - 1] == '\x01';
}

/// @brief DCC (Direct Client-to-Client) est un sous-protocole CTCP permettant des connexions directes entre utilisateurs IRC. 
///        Il est utilisé pour l'envoi de fichiers (DCC SEND) et les discussions privées (DCC CHAT), évitant ainsi de passer par le serveur IRC.(cest le client qui dispose de sa)
/// @param cmd ma strucutre de commande que jai recu
/// @return vrai si le msg est un CTCP et commence par DCC
bool Irssi_serv::_is_DCC(Cmd_irssi & cmd)
{
	std::string msg = cmd.get_message();

	// Vérifier si le message est encadré par \x01
	if (_is_CTCP(cmd))
	{
		// Enlever les \x01 et vérifier si ça commence par "DCC "
		std::string clean_msg = msg.substr(1, msg.size() - 2);
		return clean_msg.rfind("DCC ", 0) == 0;  // Vérifie si "DCC " est au début
	}
	return false;
}

void	Irssi_serv::_ft_dcc(void)
{
	std::cout << RED + "Doit faire le bonus dcc mais ne sait pas par ou commencer." + NOCOLOR << std::endl;
}