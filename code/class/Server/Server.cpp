/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:23:05 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/15 06:54:02 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

Server::Server(): _name("Prenom")
{
	std::cout << getColorCode(BLUE) << "Constructeur de Server" << std::endl;
	std::cout << getColorCode(GREEN) << "Server->_name = " << getColorCode(YELLOW) << _name << getColorCode(NOCOLOR) << std::endl;
}

Server::~Server()
{
	std::cout << getColorCode(RED) << "DEstructeur de Server" << getColorCode(NOCOLOR) << std::endl;
}
