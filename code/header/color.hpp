/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:50:27 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/15 07:06:59 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

// Définition de l'énumération
enum Color {
	NOCOLOR,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	COLOR_COUNT // Taille du tableau de couleur
};

// Tableau associé avec leur valeur ascii
extern const char* colorCodes[COLOR_COUNT];

// Retourne la valeur ascii de la couleur demande
const char* getColorCode(Color color);

