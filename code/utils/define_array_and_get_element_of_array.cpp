/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_array_and_get_element_of_array.cpp          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:09:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/23 19:00:56 by yzaoui           ###   ########.fr       */
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
	"Pas d'action",																																				// NO_ACTION
	"Probléme de la fonction recv, lors de la recpetion des données",																							// ERROR_RECV_DATA
	"Fermeture du serveur. On eteint le serveur",																												// SHUTDOWN
	"Déconexion d'un client et la supression de l'utilisateur de la bdd",																						// DISCONNECT
	"Capacite du serveur, voir argument",																														// CAP == Capablities
	"Set le nom de l'utilisateur",																																// NICK
	"Identification de l'utilisateur aupres du serveur",																										// USER
	"Definit comment est percu/definit user/channel",																											// MODE
	"Demande si la connexion est toujour etablie",																												// PING
	"Demande les infos de l'utilisateur spécifié",																												// WHOIS
	"Demande les infos d'un utilisateur qui n'existe plus",																										// WHOWAS
	"L'utilisateur se déconnecte et envoie un message aux autre utilisateurs.",																					// QUIT
	"Permet à un utilisateur de rejoindre ou cree un canal (chatroom).",																						// JOIN
	"Permet d'envoyer un message privé à un utilisateur ou un message public dans un canal.",																	// PRIVMSG
	"Renvoie une liste d'users ou des infos sur un user specifique",																							// WHO
	"Permet d'expulser un utilisateur d'un canal spécifique. Seuls les opérateurs du canal (@) ont le droit d'utiliser cette commande.",						// KICK
	"Pour inviter un utilisateur à rejoindre un canal privé (+i). Si le canal n'est pas en mode privé, l'utilisateur peut y entrer sans invitation.",			// INVITE
	"Est utilisée pour afficher ou modifier le sujet (titre) d'un canal. Seuls les opérateurs du canal peuvent modifier le sujet si le mode +t est activé.",	// TOPIC
	"Quite un chanelle.",																																		// PART
	"Permet de se connecter avec un mot de passe ??",																											// PASS
	"... Action non reconnus",																																	// IDK
};

const char* getActionString(Action current_action)
{
	int len_of_tab = int(IDK) + 1;
	int index_in_tab = int(current_action);
	if (index_in_tab >= 0 && index_in_tab < len_of_tab)
		return action_tab[index_in_tab];
	return action_tab[IDK];
}

const char* mode_tab[NO_MODE + 1] =
{
	"USER: modifie la visibilité des informations hors channel / CHAN: rend l'accés au channel sur invitation.", //I
	"Restricion sur la commande topic (limite aux opérateurs ou non).", 										 //t
	"Ajoute/supprime une clé au channel",																		 //k
	"USER: operateur réseau / CHAN: donne/supprime le titre operateur a un utilisateur",						 //o
	"Ajoute/supprime une limite d'utilisateur dans le channel",													 //l
	"Mode inconnu",																								 //NO_MODE
};

const char * getmodeString(Mode current_mode)
{
	int	len_tab = int(NO_MODE) + 1;
	int	index_in_tab = int(current_mode);
	if (index_in_tab >= 0 && index_in_tab < len_tab)
		return mode_tab[index_in_tab];
	return mode_tab[NO_MODE];
}