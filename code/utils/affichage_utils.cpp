/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage_utils.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:36:37 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 19:57:26 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/Library.hpp"

// Fonction pour convertir les événements en chaîne de caractères
std::string getEventsString(short events)
{
	std::string events_str;
	if (events & POLLIN) events_str += "POLLIN ";
	if (events & POLLOUT) events_str += "POLLOUT ";
	if (events & POLLERR) events_str += "POLLERR ";
	if (events & POLLHUP) events_str += "POLLHUP ";
	if (events & POLLNVAL) events_str += "POLLNVAL ";

	return events_str.empty() ? "None" : events_str;
}

// Fonction pour générer une ligne de séparation
void printSeparator(std::ostream &o, size_t width)
{
	o << "|" << std::string(width - 2, '-') << "|" << std::endl;
}
