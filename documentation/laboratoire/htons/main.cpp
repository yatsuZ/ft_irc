/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/15 18:15:40 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <arpa/inet.h>

uint16_t htonsExemple(uint16_t valeurHote)
{
	// Convertit la valeur de l'ordre de l'hôte vers l'ordre du réseau
	uint16_t valeurReseau = htons(valeurHote);

	// Renvoie la valeur convertie
	return valeurReseau;
}

int main(void)
{
	// Déclaration d'une variable de type `uint16_t`
	uint16_t valeurHote = 12345;

	// Appel de la fonction `htonsExemple` pour convertir la valeur
	uint16_t valeurReseau = htonsExemple(valeurHote);

	// Affichage des valeurs avec std::cout
	std::cout << "Valeur hôte: " << valeurHote << std::endl;
	std::cout << "Valeur réseau: " << valeurReseau << std::endl;

	return 0;
}
