/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:50:27 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/12 18:56:57 by yzaoui           ###   ########.fr       */
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

// Retourne la valeur ascii de la couleur demande
inline const char* getColorCode(Color color);

#include "./../ipp_folder/color.ipp"