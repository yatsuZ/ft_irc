/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/18 18:27:58 by smlamali         ###   ########.fr       */
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
_autor_topic(""), 
_creation_topic(0), 
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
_topic(""),
_autor_topic(""),
_creation_topic(0)
{
	_limit_user = 0;
	_nbr_user = 0;
	std::cout << "Channel " + _name + " created" << std::endl;
}

void	Channel::add_user(size_t idx_user)
{
	for (std::vector<size_t>::iterator i = this->_user_invite.begin(); i != this->_user_invite.end(); i++)
	{
		if (*i == idx_user)
		{
			this->_user_invite.erase(i);
			break ;
		}
	}	
	_nbr_user++;
	_index_users.push_back(idx_user);
}

void	Channel::add_invit(size_t idx_user)
{
	_user_invite.push_back(idx_user);
}

void	Channel::errase_user(size_t index_user)
{
	this->_nbr_user--;
	for (std::vector<size_t>::iterator i = this->_index_users.begin(); i != this->_index_users.end(); i++)
	{
		if (*i == index_user)
		{
			this->_index_users.erase(i);
			break ;
		}
	}
	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
	{
		if (*i == index_user)
		{
			this->_index_operators.erase(i);
			break;
		}
	}
	for (std::vector<size_t>::iterator i = this->_user_invite.begin(); i != this->_user_invite.end(); i++)
	{
		if (*i == index_user)
		{
			this->_user_invite.erase(i);
			break;
		}
	}
}


void	Channel::erase_operator(size_t index_user)
{
	this->_nbr_user--;
	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
	{
		if (*i == index_user)
		{
			this->_index_operators.erase(i);
			break ;
		}
	}
}


// void	Channel::erase_update_user(size_t idx)
// {

// }

/// @brief mets a jour lindex des user / operateur superieur aux user QUE JE DOIS SUPRIMER et suprimer si je trouve son index dans la liste de mon chanelle
/// @param index_user index du user dans irssi_serv->_all_User
void	Channel::update_and_errase_index_of_user(size_t index_user)
{
	std::cout << "L'index de lutilisateur a suprimer dans Irssi_serv::_all_User : " << index_user << std::endl;

	std::vector<size_t>::iterator to_del = this->_index_users.end();
	// std::cout << this->_index_users << std::endl;
	for (std::vector<size_t>::iterator i = this->_index_users.begin(); i != this->_index_users.end(); ++i)
	{
		// std::cout << *i << " =?= " << index_user << std::endl;
		if (*i == index_user)
		{
			// std::cout << "Trouver" << std::endl;
			to_del = i;
		}
		if (*i > index_user)
			*i = *i - 1;
	}
	if (to_del != this->_index_users.end())
	{
		// std::cout << "TO DEL" << std::endl;
		this->_index_users.erase(to_del);
	}
	else
		return;

	to_del = this->_index_operators.end();
	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
	{
		if (*i == index_user)
			to_del = i;
		if (*i > index_user)
			*i = *i - 1;
	}
	if (to_del != this->_index_operators.end())
		this->_index_operators.erase(to_del);

	to_del = this->_user_invite.end();
	for (std::vector<size_t>::iterator i = this->_user_invite.begin(); i != this->_user_invite.end(); i++)
	{
		if (*i == index_user)
			to_del = i;
		if (*i > index_user)
			*i = *i - 1;
	}
	if (to_del != this->_user_invite.end())
		this->_user_invite.erase(to_del);
	
	this->_nbr_user--;
}

std::string	Channel::mode_to_str(const Mode & m)const
{
	if (m == I)
		return ("i");
	if (m == T)
		return ("t");
	if (m == K)
		return ("k");
	if (m == O)
		return ("o");
	if (m == L)
		return ("l");
 	return ("");
}

std::string	Channel::list_mode()const
{
	std::string	list = "";
	if (_mode.empty())
		return list;
	for (size_t i=0; i<_mode.size(); i++)
		list += mode_to_str(_mode[i]);
	return list;
}

bool	Channel::is_operator(size_t	idx_user) const
{
	for(size_t i=0; i<_index_operators.size(); i++)
	{
		if (idx_user == _index_operators[i])
			return 1;
	}
	return 0;
}

bool	Channel::is_in_chan(size_t idx_user)
{
	for(size_t i=0; i<_index_users.size(); i++)
	{
		if (_index_users[i] == idx_user)
			return 1;
	}
	return 0;
}

bool	Channel::is_in_invitation(size_t idx_user)
{
	for(size_t i=0; i<_user_invite.size(); i++)
	{
		if (_user_invite[i] == idx_user)
			return 1;
	}
	return 0;
}

void	Channel::set_mode(Mode m)
{
	for (size_t i=0; i<_mode.size(); i++)
	{
		if (_mode[i] == m)
			return;
	}	
	_mode.push_back(m);
}

void	Channel::erase_mode(Mode m)
{
	for (size_t i=0; i<_mode.size(); i++)
	{
		if (_mode[i] == m)
			_mode.erase(_mode.begin() + i);
	}
}

void	Channel::set_limit(std::string l)
{
	std::stringstream sstream(l);
	size_t	rslt;
	sstream >> rslt;
	_limit_user = rslt;
}

std::string Channel::time_creation_in_string(void) const
{
	std::ostringstream oss;
	oss << this->_creation_topic;
	return oss.str();
}

bool		Channel::mode_in_channel(Mode m)
{
	for(size_t i=0; i<_mode.size(); i++)
	{
		if (_mode[i] == m)
			return 1;
	}
	return 0;
}

// void	Channel::update_index_of_user(size_t index_user)
// {
// 	for (std::vector<size_t>::iterator i = this->_index_users.begin(); i != this->_index_users.end(); i++)
// 	{
// 		if (*i > index_user)
// 			*i = *i - 1;
// 	}
// 	for (std::vector<size_t>::iterator i = this->_index_operators.begin(); i != this->_index_operators.end(); i++)
// 	{
// 		if (*i > index_user)
// 			*i = *i - 1;
// 	}
// 	for (std::vector<size_t>::iterator i = this->_user_invite.begin(); i != this->_user_invite.end(); i++)
// 	{
// 		if (*i > index_user)
// 			*i = *i - 1;
// 	}
// }

// bool found = false;
	// std::vector<size_t>::iterator to_del = this->_index_users.end();
	// for (std::vector<size_t>::iterator i = _index_users.end(); i != _index_users.end(); i++)
	// {
	// 	if (*i == idx)
	// 	{
	// 		to_del = i;
	// 		found = true;
	// 		_index_users.erase(to_del);
	// 	}
	// 	else if (*i > idx)
	// 		*i = *i - 1;
	// }
	// if (!found)
	// {
	// 	std::cout << "###User not found####" << std::endl;
	// 	return ;
	// }

	// to_del = this->_index_operators.end();
	// for (std::vector<size_t>::iterator i = _index_operators.end(); i != _index_operators.end(); i++)
	// {
	// 	if (*i == idx)
	// 	{
	// 		to_del = i;
	// 		found = true;
	// 	}
	// 	else if (*i > idx)
	// 		*i = *i - 1;
	// }
	// if (found)
	// 	_index_operators.erase(to_del);

	// to_del = this->_user_invite.end();
	// for (std::vector<size_t>::iterator i = _user_invite.end(); i != _user_invite.end(); i++)
	// {
	// 	if (*i == idx)
	// 	{
	// 		to_del = i;
	// 		found = true;
	// 	}
	// 	else if (*i > idx)
	// 		*i = *i - 1;
	// }
	// if (found)
	// 	_user_invite.erase(to_del);