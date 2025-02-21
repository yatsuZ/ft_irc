/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/21 19:48:59 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(){}

Channel::~Channel(){}

Channel::Channel(const std::string & n, const std::string & k) : _name(n), 
_key(k), _topic("")
{
	_limit_user = 0;
	std::cout << "Channel " + _name + " created" << std::endl;
}


void	Channel::add_user(size_t idx_user)
{_users.push_back(idx_user);}