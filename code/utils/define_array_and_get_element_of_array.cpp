/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_array_and_get_element_of_array.cpp          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 23:09:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/28 00:55:46 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/Library.hpp"

const char* colorCodes[COLOR_COUNT] = {
	"\033[0m",  // NOCOLOR
	"\033[31m", // RED
	"\033[32m", // GREEN
	"\033[33m", // YELLOW
	"\033[34m", // BLUE
	"\033[35m", // MAGENTA
	"\033[36m", // CYAN
	"\033[37m", // WHITE
};

const char* getColorCode(Color color)
{
	if (color >= 0 && color < COLOR_COUNT)
		return colorCodes[color];
	return "\033[0m"; // Couleur par défaut
}

const char* action_tab[IDK + 1] =
{
	"Pas d'action", // NO_ACTION
	"Probléme de la fonction recv, lors de la recpetion des données", // ERROR_RECV_DATA
	"Fermeture du serveur. On eteint le serveur", // SHUTDOWN
	"Déconexion d'un client", // DISCONNECT
	"Set le nom de l'utilisateur", //NICK
	"... Action non reconnus", // IDK
};

const char* getActionString(Action current_action)
{
	if (current_action >= 0 && current_action < IDK + 1)
		return action_tab[current_action];
	return action_tab[IDK];
}