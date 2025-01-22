/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:43:08 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 01:39:52 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/color.hpp"

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
	"Fermetur du serveur. On etein le serveur", // SHUTDOWN
	"Déconexion d'un client", // DECO
	"... Action non reconnus", // IDK
};

const char* getActionString(Action current_action)
{
	if (current_action >= 0 && current_action < IDK + 1)
		return action_tab[current_action];
	return action_tab[IDK];
}


std::ostream & operator<<( std::ostream & o, Action const & action)
{
	o << std::string(getActionString(action));
	return (o);
}
std::ostream & operator<<( std::ostream & o, Color const & color)
{
	o << std::string(getColorCode(color));
	return (o);
}
