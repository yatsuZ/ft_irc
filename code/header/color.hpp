/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:50:27 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/20 01:44:03 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>

#define ADDRESSE_IP_IN "127.0.0.1"
// #define ADDRESSE_IP_IN "10.13.1.13"
#define REUSEADDR_OPTION 1
// #define BUFFER_SIZE 1
// #define BUFFER_SIZE 2
#define BUFFER_SIZE 1024
#define MAX_EVENTS 10


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

enum Action {
	NO_ACTION,
	ERROR_RECV_DATA,
	SHUTDOWN,
	DECO,
	IDK
};

// Tableau associé avec leur valeur ascii
extern const char* colorCodes[COLOR_COUNT];

// Retourne la valeur ascii de la couleur demande
const char* getColorCode(Color color);

