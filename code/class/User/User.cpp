/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/02/03 12:59:49 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void): _nick(""), _name("")
{
	std::cout << "A new User is joining" << std::endl;
}

User::User(std::string & nick): _nick(nick), _name("")
{
	std::cout << "A new User is joining" << std::endl;
}

User::~User(){}

std::string User::getName()
{return _nick;}

void	User::setName(const std::string & n)
{_nick = n;}

std::string User::getNick()
{return _nick;}

void	User::setNick(const std::string & n)
{_nick = n;}
