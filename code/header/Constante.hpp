/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Constante.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 19:19:43 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/12 18:42:24 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Reponse_numeric_serv.hpp"

#define SERVER_NAME "YASACO"
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
	MODE,
	PING,
	WHOIS,
	QUIT,
	JOIN,
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

enum Fonctionalite_du_serveur {
	CAP_SERV,
	NICK_SERV,
	USER_SERV,
	NBR_DE_FONCTIONALITE_DU_SERV // dernier element
};

// Tableau associé avec leur valeur d'Fonctionalite_du_serveur
extern const char* Fonctionalite_du_serveur_tab[NBR_DE_FONCTIONALITE_DU_SERV];


enum Mode_User
{
	I,		//modifie la visibilité des informations (WHOIS) hors chan
	NONE_MODE
};

// extern const char* user_mode[NONE_MODE];

// enum Mode_Channel
// {
// 	I,		// modifie la visibilité des informations (WHO) hors chan
// 	T,		// restrictions cmd TOPIC
// 	K,		// ajoute/supprime clé du canal
// 	O,		// donne/supprime privilege operator canal a un user
// 	L,		// definit/supprime limite d'utilisateur dans le canal
// 	NONE_MODE
// };

extern const char* channel_mode[NONE_MODE];