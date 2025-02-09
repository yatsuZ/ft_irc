/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:45 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/09 17:05:46 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./UserHuman.hpp"

UserHuman::UserHuman(void): User(), Client()
{
}

UserHuman::UserHuman(std::string & nick, Client & client): User(nick), Client(client)
{
	std::cout << "User Human \"" << PINK << nick << NOCOLOR << "\" is joining" << std::endl;
}


UserHuman::UserHuman(Client & client): User(), Client(client)
{
	std::cout << "User Human \"" << PINK << this->getName() << NOCOLOR << "\" is joining" << std::endl;
}

UserHuman::~UserHuman(){}
