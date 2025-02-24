/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/25 00:09:44 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

	// std::string					_name;
	// std::string					_key;
	// std::string					_topic;
	// std::vector<size_t> 		_index_users;
	// std::vector<size_t>			_index_operators;
	// size_t						_nbr_user;
	// size_t						_limit_user;
	// std::vector<Mode_Channel>	_mode; //?


Channel::Channel() :
_name("default_name"), 
_key(""), 
_topic(""), 
_index_users(), 
_index_operators(), 
_nbr_user(0),
_limit_user(0),
_mode()
{}

Channel::~Channel(){}

Channel::Channel(const std::string & n, const std::string & k) : 
_name(n), 
_key(k), 
_topic("")
{
	_limit_user = 0;
	_nbr_user = 0;
	std::cout << "Channel " + _name + " created" << std::endl;
}

void	Channel::add_user(size_t idx_user)
{
	_nbr_user++;
	_index_users.push_back(idx_user);
}


void	Channel::errase_user(size_t index_user)
{
	for (std::vector<size_t>::iterator i = this->_index_users.begin(); i != this->_index_users.end(); i++)
	{
		if (*i == index_user)
			this->_index_users.erase(i);
	}
	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
	{
		if (*i == index_user)
			this->_index_operators.erase(i);
	}
}

void	Channel::update_index_of_user(size_t index_user)
{
	for (std::vector<size_t>::iterator i = this->_index_users.begin(); i != this->_index_users.end(); i++)
	{
		if (*i > index_user)
			*i = *i - 1;
	}
	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
	{
		if (*i > index_user)
			*i = *i - 1;
	}
}

/// @brief mets a jour lindex des user / operateur superieur aux user QUE JE DOIS SUPRIMER et suprimer si je trouve son index dans la liste de mon chanelle
/// @param index_user index du user dans irssi_serv->_all_User
void	Channel::update_and_errase_index_of_user(size_t index_user)
{
	for (std::vector<size_t>::iterator i = this->_index_users.begin(); i != this->_index_users.end(); i++)
	{
		if (*i == index_user)
			this->_index_operators.erase(i);
		if (*i > index_user)
			*i = *i - 1;
	}
	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
	{
		if (*i == index_user)
			this->_index_operators.erase(i);
		if (*i > index_user)
			*i = *i - 1;
	}
}
