/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:45:46 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 20:31:14 by yzaoui           ###   ########.fr       */
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

