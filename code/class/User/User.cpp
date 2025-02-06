/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/02/06 16:19:36 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void): _nick(""), _name("")
{
	// std::cout << "A Default User is joining" << std::endl;
}

User::User(std::string & nick): _nick(nick), _name("guest")
{
	// std::cout << "A Parametrick User with nick " << PINK << nick << NOCOLOR << " is joining" << std::endl;
}

User::~User(){}


// --- GETTERS
std::string User::getNick()
{return _nick;}

std::string User::getName()
{return _name;}

std::string User::getHostname()
{return _hostname;}

std::string User::getRealname()
{return _realname;}

std::string User::getServername()
{return _servername;}

// --- SETTERS ---
void	User::setName(const std::string & n)
{_name = n;}

void	User::setNick(const std::string & n)
{_nick = n;}

void	User::setHostname(const std::string & h)
{_hostname = h;}

void	User::setRealname(const std::string & n)
{_realname = n;}

void	User::setServername(const std::string & s)
{_servername = s;}
