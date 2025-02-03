/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:45 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/03 13:00:16 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./UserHuman.hpp"

UserHuman::UserHuman(void)
{
}

UserHuman::UserHuman(std::string & nick, Client & client): User(nick), Client(client)
{
	std::cout << "A new User is joining" << std::endl;
}

UserHuman::~UserHuman(){}
