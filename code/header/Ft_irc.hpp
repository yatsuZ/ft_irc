/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:45:46 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 12:17:07 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Library.hpp"

std::string getEventsString(short events);
void printSeparator(std::ostream &o, size_t width);
// Retourne la valeur ascii de la couleur demande
const char* getColorCode(Color color);

// Retourne l'action en string 
const char* getActionString(Action current_action);

bool	compare_str_char(const char &c, const std::string& str);
long ft_atol_limits(const std::string& str, long min, long max, bool *error);
std::string intToString(int value);
ssize_t	is_sep(char c, std::string str);
std::vector<std::string> ft_split(const std::string& , const std::string& );

std::ostream & operator<<( std::ostream & o, Action const & action);
std::ostream & operator<<( std::ostream & o, Color const & color);

/////////////////////////////////////// A SUPRIMER

void	Message_a_sam(void);
void	Message_de_sam(void);
void	Message_de_yaya(void);
void	afficher_texte_progressivement(std::string texte, int delai_s);
void	TO_DO(void);
int		send_message(std::string message, pollfd &current_pollfd);

std::string operator+(Color const& color, std::string const& str);
std::string operator+(std::string const& str, Color const& color);
std::string operator+(Color const& color, const char * str);
std::string operator+(const char * str, Color const& color);

