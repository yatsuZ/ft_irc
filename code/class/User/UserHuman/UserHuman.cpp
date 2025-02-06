/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:45 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/06 19:57:43 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./UserHuman.hpp"

UserHuman::UserHuman(void)
{
}

UserHuman::UserHuman(std::string & nick, Client & client): User(nick), Client(client)
{
	std::cout << "User Human \"" << PINK << nick << NOCOLOR << "\" is joining" << std::endl;
}

UserHuman::~UserHuman(){}
