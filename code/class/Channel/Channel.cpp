/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/23 19:53:57 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() : _name("chan"), _key(""){}

Channel::~Channel(){}

Channel::Channel(const std::string & n, const std::string & k) : _name(n), 
_key(k), _topic("")
{
	_limit_user = 0;
	std::cout << "Channel " + _name + " created" << std::endl;
}

// void	Channel::add_user(size_t idx_user)
// {_users.push_back(idx_user);}

void	Channel::add_user(User * u)
{_users.push_back(*u);}

std::string Channel::list_user(void)const
{
	std::string	list = "";
	if (_users.empty())
	{
		std::cout << "no users found in channel" << std::endl;
		return list;
	}
	for (size_t i=0; i<_users.size(); i++)
	{
		list += "@" + _users[i].get_nick();
		if (i + 1 < _users.size())
			list += " ";
	}
	return list;
}