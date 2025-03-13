/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:45:46 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/13 17:58:01 by yzaoui           ###   ########.fr       */
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

bool						target_is_chanelle(std::string & arg1);
bool						compare_str_char(const char &c, const std::string& str);
long 						ft_atol_limits(const std::string& str, long min, long max, bool *error);
std::string 				intToString(int value);
ssize_t						is_sep(char c, std::string str);
std::vector<std::string> 	ft_split(const std::string& , const std::string& );
std::vector<std::string>	ft_split2(const std::string & str, const std::string & sep);


std::ostream & operator<<( std::ostream & o, Action const & action);
std::ostream & operator<<( std::ostream & o, Color const & color);
std::ostream & operator<<( std::ostream & o, std::vector<size_t> const & vec_of_size_t);
std::ostream & operator<<( std::ostream & o, Mode const & mode);
std::ostream & operator<<( std::ostream & o, std::vector<Mode> const & vec_of_mode);
std::ostream & operator<<( std::ostream & o, std::vector<std::string> const & list_of_word);

int		send_message(std::string message, pollfd &current_pollfd);

std::string operator+(Color const& color, std::string const& str);
std::string operator+(std::string const& str, Color const& color);
std::string operator+(Color const& color, const char * str);
std::string operator+(const char * str, Color const& color);

/////////////////////////////////////// A SUPRIMER

void	Message_a_sam(void);
void	Message_de_sam(void);
void	Message_de_yaya(void);
void	afficher_texte_progressivement(std::string texte, int delai_s);
void	TO_DO(void);