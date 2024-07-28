/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/15 18:28:25 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <iostream>

int main(void)
{
	// Déclaration de variables
	uint32_t valeurHote1 = 10000;		// Valeur hôte (little-endian)
	uint32_t valeurHote2 = 4294967294;	// Valeur hôte (proche de la valeur maximale)
	uint32_t valeurReseau1;
	uint32_t valeurReseau2;

	// Conversion des valeurs et affichage des résultats
	std::cout << "Valeur hôte 1 (little-endian): " << valeurHote1 << std::endl;
	valeurReseau1 = htonl(valeurHote1);
	std::cout << "Valeur réseau 1: " << valeurReseau1 << std::endl;

	std::cout << "\nValeur hôte 2 (proche de la valeur maximale): " << valeurHote2 << std::endl;
	valeurReseau2 = htonl(valeurHote2);
	std::cout << "Valeur réseau 2: " << valeurReseau2 << std::endl;

	return 0;
}
