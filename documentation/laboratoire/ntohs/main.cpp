/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/15 19:30:30 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <iostream>

int main()
{
	// Déclaration des variables
	uint16_t valeurReseau = 0x1234; // Valeur réseau (big-endian)
	uint16_t valeurHote;

	// Conversion de la valeur réseau et affichage du résultat
	std::cout << "Valeur réseau (big-endian): 0x" << std::hex << valeurReseau << std::endl;
	valeurHote = ntohs(valeurReseau);
	std::cout << "Valeur hôte (little-endian): 0x" << std::hex << valeurHote << std::endl;

	return 0;
}
