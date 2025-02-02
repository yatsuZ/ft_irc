/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constante.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:19:43 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/28 00:52:45 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
	PINK,
	COLOR_COUNT // Taille du tableau de couleur
};

// Tableau associé avec leur valeur ascii
extern const char* colorCodes[COLOR_COUNT];


//Important si changment apliquer dans le tableau action_tab (juste en bas)
enum Action {
	NO_ACTION,
	ERROR_RECV_DATA,
	SHUTDOWN,
	DISCONNECT,
	CAP,
	NICK,
	USER,
	IDK// derniere Action du tableau
};

// Tableau associé avec leur valeur d'action
extern const char* action_tab[IDK + 1];

//Important si changment apliquer dans le tableau action_tab
enum Reaction_Serv {
	NONE,
	PASS,
	STOP
};


#define SEPERATOR_WITHOUT_SPACE_AND_TAB "\n\v\f\r"
#define SEPERATOR " \t\n\v\f\r"