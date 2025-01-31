/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/01/31 01:19:41 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void): _name(""), _nick("")
{
	std::cout << "A new User is joining" << std::endl;
}

User::User(std::string & name): _name(name), _nick("")
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
