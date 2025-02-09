/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/02/09 19:32:07 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void):
 _nick("*"), _name("guest"), _hostname(""), _real_name("Guest"),
  _servername(SERVER_NAME), _droit_user(NONE_MODE), _set_user(false) 
{
	// std::cout << "A Default User is joining" << std::endl;
}

User::User(std::string & nick): _nick(nick), _name("guest"), _droit_user(NONE_MODE), _set_user(false)
{
	// std::cout << "A Parametrick User with nick " << PINK << nick << NOCOLOR << " is joining" << std::endl;
}

User::~User(){}

// --- SETTERS ---
void	User::setName(const std::string & n)
{_name = n;}

void	User::setNick(const std::string & n)
{_nick = n;}

void	User::setHostname(const std::string & h)
{_hostname = h;}

void	User::setRealname(const std::string & n)
{_real_name = n;}

void	User::setServername(const std::string & s)
{_servername = s;}
