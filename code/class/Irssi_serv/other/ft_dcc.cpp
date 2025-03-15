/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dcc.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:48:54 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/16 00:20:29 by yzaoui           ###   ########.fr       */
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

/// @return retorune la commande cmd sans les /x01
std::string Irssi_serv::_clean_dcc_cmd(Cmd_irssi & cmd)
{
	std::string msg = cmd.get_message();
	if (msg.length() < 2)
		return (msg);
	return (msg = msg.substr(1, msg.length() - 2), msg);
}

static	std::vector<std::string>	rafinement_des_param_dcc(std::string & param_dcc)
{
	std::vector<std::string> separete_by_space_and_quote = ft_split(param_dcc, " \"\'");
	std::vector<std::string> list_param_dcc;
	std::string				to_add = "";
	bool quote = false;
	for (size_t i = 0; i < separete_by_space_and_quote.size(); i++)
	{
		if (separete_by_space_and_quote[i] == "\"")
			quote = !quote;
		else if (quote || (!quote && separete_by_space_and_quote[i] != " "))
			to_add += separete_by_space_and_quote[i];
		if (!quote && to_add.empty() == false)
		{
			list_param_dcc.push_back(to_add);
			to_add = "";
		}
	}
	if (to_add.empty() == false)
		list_param_dcc.push_back(to_add);
	return (list_param_dcc);
}

bool	Irssi_serv::_ft_dcc(std::string param_dcc, UserHuman & emeteur , ssize_t index_emeteur, ssize_t index_recepteur, pollfd & emeteur_pollfd, UserHuman & recepteur)
{
	std::cout << RED + "DCC REQUEST." + NOCOLOR << std::endl;
	// std::cout << RED + "MSG = \"" << PINK << param_dcc << "\"" << NOCOLOR << std::endl;
	
	std::vector<std::string> list_param_dcc = rafinement_des_param_dcc(param_dcc);
	// std::cout << YELLOW + "RAFINEMENT = " << NOCOLOR << list_param_dcc << std::endl;

	Dcc test(list_param_dcc, index_emeteur, index_recepteur);
	if (test.get_valide_dcc() == false)
		return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "Error in creation of dcc request."), emeteur_pollfd), false);
	else if (test.get_type() == SEND_DCC)
	{
		if (emeteur.add_request_send_file(test) == false)
			return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "DCC request already in progress, for the file \"" + test.get_file_name() + "\"."), emeteur_pollfd), false);
		/*TCP CONNEXION*/
	}
	else if (test.get_type() == GET_DCC)// JE ne pass pas par ici car je n'arive pas a recuoere DCC get
	{// chercher dans le tableaux des requette // faire la transmission de fichier et suprimer du tableau
		Dcc send_request = recepteur.pop_request_dcc(test);
		if (send_request.get_valide_dcc() == false)
			return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "No DCC request issued by " + recepteur.get_nick() + " for the file \"" + test.get_file_name() + "\""), emeteur_pollfd), false);
		if (_transfer_file(send_request, test, recepteur, emeteur) == false)
			return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "Faillure transfer files"), emeteur_pollfd), false);

	}
	else /*type de dcc comande inreconnue*/
		return (send_message(NOTICE(this->get_name(), emeteur.get_nick(), "unrecognized dcc request."), emeteur_pollfd), false);
	return (true);
}

bool	Irssi_serv::_transfer_file(Dcc & send, Dcc & get, UserHuman & author_send, UserHuman & author_get)
{
	(void) send;
	(void) get;
	(void) author_send;
	(void) author_get;

	/*ICI FAIRE LE TRANSFERT DE FICHIET PUIS SUPRIMER ??*/
	std::cout << "Faire le transfert de fichier." << std::endl;

	return (true);
}
