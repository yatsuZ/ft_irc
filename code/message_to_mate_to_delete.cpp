/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_to_mate_to_delete.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:19:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/06 20:14:25 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./class/Irssi_serv/Irssi_serv.hpp"

void TO_DO(void)
{
	std::cout << BLUE << "SALUT ! Voici ce qu'il y a à faire." << NOCOLOR << std::endl;

	std::cout << "1. " << CYAN << "Faire l'interprétation des actions reçues du client irssi." << NOCOLOR << std::endl;
	std::cout << "\t- Aller dans le fichier " << YELLOW << "./class/Cmd_irssi/Cmd_irssi.cpp" << NOCOLOR
			  << " et modifier la méthode : " << MAGENTA << "Cmd_irssi::init_action(void)" << NOCOLOR << "." << std::endl;

	std::cout << "2. " << GREEN << "Pour interpréter la première commande :" << NOCOLOR << std::endl;
	std::cout << "\t- Modifier " << YELLOW << "./header/Constante.hpp" << NOCOLOR
			  << " pour ajouter une nouvelle action dans l'énumération " << RED << "ACTION" << NOCOLOR << "." << std::endl;
	std::cout << "\t- Respecter les commentaires et l'ordre, c'est très important !" << std::endl;

	std::cout << "3. " << CYAN << "Ajouter le message associé à cette nouvelle action dans le fichier :" << NOCOLOR << std::endl;
	std::cout << "\t- " << YELLOW << "./utils/define_array_and_get_element_of_array.cpp" << NOCOLOR << "." << std::endl;

	std::cout << "4. " << MAGENTA << "Pour finir :" << NOCOLOR << std::endl;
	std::cout << "\t- Créer la nouvelle méthode pour l'action dans " << YELLOW << "./class/Irssi_serv/Irssi_serv.hpp" << NOCOLOR << "." << std::endl;
	std::cout << "\t- Ne pas oublier de l'ajouter dans le constructeur dans " << YELLOW << "./class/Irssi_serv/Irssi_serv.cpp" << NOCOLOR << "." << std::endl;

	std::cout << std::endl;
	std::cout << RED << "/!\\ IMPORTANT : Respecter l'ordre et les commentaires pour éviter les erreurs." << NOCOLOR << std::endl;
	std::cout << std::endl;
	std::cout << "---------------------------" << std::endl;
	std::cout << WHITE << "-- BONNE CHANCE --" << GREEN << " (O_<)★彡" << NOCOLOR << std::endl;
}

void afficher_texte_progressivement(std::string texte, int delai_s = 25000)
{
	for (size_t i = 0; i < texte.length(); ++i)
	{
		std::cout << texte[i] << std::flush;
		usleep(delai_s);  // Attente entre chaque caractère en secondes
	}
	std::cout << std::endl;
}

void Message_a_sam(void)
{
	std::string msg = std::string(getColorCode(RED)) + "Si tu as lu ce message, envoie un message sur Instagram, comme sa je sais que tu essaies de lire le code -_-." + std::string(getColorCode(NOCOLOR)) ;
	afficher_texte_progressivement(msg);
	msg = std::string(getColorCode(PINK)) + "Salut SAM ! Voici ce qu'il y a à faire :\n" + std::string(getColorCode(NOCOLOR)) ;

	afficher_texte_progressivement(msg);
	msg = std::string("1. " + std::string(getColorCode(CYAN)) + "Compléter les réponses du serveur dans " + std::string(getColorCode(YELLOW)) + "./class/Irssi_serv/action_serv/nick.cpp" + std::string(getColorCode(NOCOLOR))) ;

	afficher_texte_progressivement(msg);

	msg = std::string(std::string(getColorCode(BLUE)) + "\t- Tu dois t'occuper de USER NICK, CAP n'est pas obligatoire.\n" + std::string(getColorCode(NOCOLOR))) ;
	msg = std::string(std::string(getColorCode(MAGENTA)) + "\t- + Adapter les reponse en fonction de la norme RPL. Et aller dans " + std::string(getColorCode(YELLOW)) + "./header/Reponse_numeric_serv.hpp" + std::string(getColorCode(NOCOLOR)) + " .\n" + std::string(getColorCode(NOCOLOR))) ;

	afficher_texte_progressivement(msg);

	std::cout << std::endl;
	afficher_texte_progressivement("/!\\ INFO : En regardant le code d'Ilhame, elle a créé des macros pour automatiser les messages, mais je ne sais pas quand les utiliser.\nRegarde dans " + std::string(getColorCode(YELLOW)) + " header/Reponse_numeric_serv.hpp\n"+ std::string(getColorCode(NOCOLOR)));

	std::cout << std::endl;
	afficher_texte_progressivement("---------------------------");
	afficher_texte_progressivement("------ BONNE CHANCE -------");
	afficher_texte_progressivement(std::string(getColorCode(PINK)) + "      (O_<)★彡. . . ." + std::string(getColorCode(NOCOLOR)), 30000 * 5);

}


void	Message_de_sam(void)
{
	std::string msg = std::string(getColorCode(PINK)) + "Samira: il me reste une chose a check pour USER puis je regarderai pour JOIN !" + std::string(getColorCode(NOCOLOR));
	afficher_texte_progressivement(msg);

	msg = std::string(getColorCode(PINK)) + "J'ai fait une reponse custom pour USER comme je ne vois pas de reponse predefinie sur cette cmd" + std::string(getColorCode(NOCOLOR));
	afficher_texte_progressivement(msg);

}

void Message_de_yaya(void)
{
	std::string msg = YELLOW + "Yassine: " + BLUE + "OKI DOKI !!" + NOCOLOR;
	afficher_texte_progressivement(msg);

	msg = MAGENTA + "\tA present je vais renetoyer mon code metre des const si possible et faire mieux databuffer" + NOCOLOR;
	afficher_texte_progressivement(msg);

	msg = PINK + "\tet aussi faire les commande: " + YELLOW + "MODE JOIN etc" + NOCOLOR + " + verifeir ce qu a fais sam.";
	afficher_texte_progressivement(msg);

	msg = GREEN + "\tD'ailleur j'ai refais la documentation de irssi" + NOCOLOR;
	afficher_texte_progressivement(msg);

}
