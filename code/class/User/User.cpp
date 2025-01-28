/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/01/28 00:46:15 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void)
{
	std::cout << "A new User is joining" << std::endl;
}

User::~User(){}

std::string User::getNick()
{return _nick;}

void	User::setNick(const std::string & n)
{_nick = n;}
