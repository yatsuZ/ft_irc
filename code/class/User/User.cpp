/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:58:28 by kuro              #+#    #+#             */
/*   Updated: 2025/03/05 18:30:00 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void):
 _nick("*"), _name("guest"), _hostname(""), _real_name("Guest"),
  _servername(SERVER_NAME), _msg_leave(""), _mode(NO_MODE), _is_init(0)
{
	// std::cout << "A Default User is joining" << std::endl;
}

User::User(std::string & nick):
 _nick(nick), _name("guest"), _hostname(""), _real_name("Guest"),
  _servername(SERVER_NAME), _msg_leave(""), _mode(NO_MODE), _is_init(0)
{
	// std::cout << "A Parametrick User with nick " << PINK << nick << NOCOLOR << " is joining" << std::endl;
}

User::~User(){}

// --- SETTERS ---
void	User::set_name(const std::string & n)
{_name = n;}

void	User::set_nick(const std::string & n)
{_nick = n;}

void	User::set_hostname(const std::string & h)
{_hostname = h;}

void	User::set_Realname(const std::string & n)
{_real_name = n;}

void	User::set_servername(const std::string & s)
{_servername = s;}

void	User::set_mode(Mode newmode)
{
	if (_mode == newmode)
		_mode = NO_MODE;
	else
		_mode = newmode;
}

void	User::add_chan(size_t idx_of_chan)
{
	_chans.push_back(idx_of_chan);
}

void	User::errase_chan(size_t index_chan)
{
	for (std::vector<size_t>::iterator i = this->_chans.begin(); i != this->_chans.end(); i++)
	{
		if (*i == index_chan)
			this->_chans.erase(i);
	}
}

void	User::update_index_of_chan(size_t index_chan)
{
	for (std::vector<size_t>::iterator i = this->_chans.begin(); i != this->_chans.end(); i++)
	{
		if (*i > index_chan)
			*i = *i - 1;
	}
}

/// @brief mets a jour lindex de chanelle superieur aux chanelle QUE JE DOIS SUPRIMER et suprimer si je trouve son index dans la liste de mon user
/// @param index_chan index du chanelle dans irssi_serv->_all_Channel
void	User::update_and_errase_index_of_chan(size_t index_chan)
{
	// std::cout << "L'index du chanelle a suprimer dans Irssi_serv::_all_Chanelle : " << index_chan << std::endl;

	std::vector<size_t>::iterator to_del = this->_chans.end();
	std::cout <<  this->_chans << std::endl;
	for (std::vector<size_t>::iterator i = this->_chans.begin(); i != this->_chans.end(); i++)
	{
		// std::cout << *i << " =?= " << index_chan << std::endl;
		if (*i == index_chan)
		{
			// std::cout << "Trouver" << std::endl;
			to_del = i;
		}
		if (*i > index_chan)
			*i = *i - 1;
	}
	if (to_del != this->_chans.end())
	{
		// std::cout << "TO DEL" << std::endl;
		this->_chans.erase(to_del);
	}
}

//retourne mode sous forme de charactère
std::string	User::mode_to_str(const Mode & m)const
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
std::string	User::list_mode()const
{
	std::string 	mode = mode_to_str(_mode);
	return mode;
}