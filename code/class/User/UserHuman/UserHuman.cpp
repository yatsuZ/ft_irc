/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:45 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/31 01:21:53 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./UserHuman.hpp"

UserHuman::UserHuman(void)
{
}

UserHuman::UserHuman(std::string & name, Client & client): User(name), Client(client)
{
	std::cout << "A new User is joining" << std::endl;
}

UserHuman::~UserHuman(){}
