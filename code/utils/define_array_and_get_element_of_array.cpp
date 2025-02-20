/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_array_and_get_element_of_array.cpp          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:09:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 10:33:43 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/Library.hpp"

const char* colorCodes[COLOR_COUNT] = {
	"\033[0m",			// NOCOLOR
	"\033[31m",			// RED
	"\033[32m",			// GREEN
	"\033[33m",			// YELLOW
	"\033[34m",			// BLUE
	"\033[35m",			// MAGENTA
	"\033[36m",			// CYAN
	"\033[37m",			// WHITE
	"\033[38;5;213m",	// PINK
};

const char* getColorCode(Color color)
{
	if (color >= 0 && color < COLOR_COUNT)
		return colorCodes[color];
	return "\033[0m"; // Couleur par défaut
}

const char* action_tab[IDK + 1] =
{
	"Pas d'action",																	// NO_ACTION
	"Probléme de la fonction recv, lors de la recpetion des données",				// ERROR_RECV_DATA
	"Fermeture du serveur. On eteint le serveur",									// SHUTDOWN
	"Déconexion d'un client et la supression de l'utilisateur de la bdd",			// DISCONNECT
	"Capacite du serveur, voir argument",											// CAP == Capablities
	"Set le nom de l'utilisateur",													// NICK
	"Identification de l'utilisateur aupres du serveur",							// USER
	"definit comment est percu/definit user/channel",								// MODE
	"Demande si la connexion est toujour etablie",									// PING
	"Demande les infos de l'utilisateur spécifié",									// WHOIS
	"L\'utilisateur se déconnecte et envoie un message aux autre utilisateurs.",	// QUIT
	"Je ne sais pas quoi faire avec JOIN",
	"Je ne sais pas quoi faire avec PRIVMSG",										// PRIVMSG
	"... Action non reconnus",														// IDK
};

const char* getActionString(Action current_action)
{
	int len_of_tab = int(IDK) + 1;
	int index_in_tab = int(current_action);
	if (index_in_tab >= 0 && index_in_tab < len_of_tab)
		return action_tab[index_in_tab];
	return action_tab[IDK];
}

const char* Fonctionalite_du_serveur_tab[NBR_DE_FONCTIONALITE_DU_SERV] =
{
	"CAP",	// CAP
	"NICK",	// NICK
	"USER",	// USER
};

// const char* user_mode()
// {
// 	"i", //invisible
// };