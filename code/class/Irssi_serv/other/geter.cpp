/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geter.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:24:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/09 17:22:30 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

UserHuman * Irssi_serv::_get_userhuman_by_index_of_pollfd(ssize_t i)
{
	if (i == -1)
		return (NULL);
	for (size_t j = 0; j < this->_all_User.size(); j++)
	{
		if (this->_all_User[j].get_index_pollfd() == i)
			return (&(this->_all_User[j]));
	}
	return (NULL);
}

UserHuman	* Irssi_serv::_get_userhuman_by_nick(const std::string & nick)
{
	for (size_t i = 0; i < this->_all_User.size(); i++)
	{
		if (this->_all_User[i].get_nick() == nick)
			return (&(this->_all_User[i]));
	}
	return (NULL);
}

Channel	*	Irssi_serv::_get_channel_by_name(const std::string & name)
{
	if (_all_Channel.empty())
		return (NULL);

	for (size_t i=0; i<_all_Channel.size(); i++)
	{
		if (_all_Channel[i].get_name() == name)
			return (&(this->_all_Channel[i])); 
	}
	return (NULL);
}

ssize_t  Irssi_serv::_get_index_channel_by_name(const std::string & name)
{
	for (size_t i = 0; i < this->_all_Channel.size(); i++)
	{
		if (this->_all_Channel[i].get_name() == name)
			return (i);
	}
	return (-1);
}


std::string Irssi_serv::get_all_chan_name_from_user(const UserHuman & user)
{
	std::vector<size_t> list_of_index_chan = user.get_chans();
	std::string	list = "";
	if (list_of_index_chan.empty())
		return list;
	for (size_t i = 0; i < list_of_index_chan.size(); i++)
	{
		
		list += this->_all_Channel[list_of_index_chan[i]].get_name();
		if (i + 1 < list_of_index_chan.size())
			list += " ";
	}
	return list;

}

std::string Irssi_serv::get_all_nick_from_chan(const Channel & chan)
{
	std::vector<size_t> list_of_index_user = chan.get_index_users();
	std::vector<size_t> list_of_index_operator = chan.get_index_operators();
	std::vector<size_t> list_of_index_all_user;//list_of_index_user + list_of_index_operator

	list_of_index_all_user.insert(list_of_index_all_user.end(), list_of_index_user.begin(), list_of_index_user.end());
	list_of_index_all_user.insert(list_of_index_all_user.end(), list_of_index_operator.begin(), list_of_index_operator.end());


	std::string	list = "";
	if (list_of_index_all_user.empty())
		return list;
	for (size_t i=0; i < list_of_index_all_user.size(); i++)
	{
		list += "@" + this->_all_User[list_of_index_all_user[i]].get_nick();
		if (i + 1 < list_of_index_all_user.size())
			list += " ";
	}
	return list;
}

std::string Irssi_serv::get_all_user_nick_from_chan(const Channel & chan)
{
	std::vector<size_t> list_of_index_all_user = chan.get_index_users();

	std::string	list = "";
	if (list_of_index_all_user.empty())
		return list;
	for (size_t i=0; i < list_of_index_all_user.size(); i++)
	{
		if (chan.is_operator(list_of_index_all_user[i]))
			list += "@";
		list += this->_all_User[list_of_index_all_user[i]].get_nick();
		if (i + 1 < list_of_index_all_user.size())
			list += " ";
	}
	return list;
}

ssize_t  Irssi_serv::_get_index_of_userhuman_by_nick(const std::string & nick)
{
	for (size_t i = 0; i < this->_all_User.size(); i++)
	{
		ssize_t j = i;
		if (this->_all_User[i].get_nick() == nick)
			return (j);
	}
	return (-1);
}

Channel * Irssi_serv::_find_chan_in_user_by_name(UserHuman & emeteur, std::string & name_chan)
{
	std::vector<size_t> list_of_index_chan = emeteur.get_chans();
	if (list_of_index_chan.empty())
		return (NULL);
	for (size_t i = 0; i < list_of_index_chan.size(); i++)
	{
		if (this->_all_Channel[list_of_index_chan[i]].get_name() == name_chan)
			return (&(this->_all_Channel[list_of_index_chan[i]]));
	}
	return (NULL);

}

///
Mode	Irssi_serv::get_mode(std::string & arg)
{
	char name_mode[5] = {'i','t','k','o','l'};
	if (arg.empty() || arg.size() > 2)
		return (NO_MODE);
	for (size_t i=0; i<5; i++)
	{
		if (arg.size() == 2 && arg[1] == name_mode[i])
			return init_mode(name_mode[i]);	
		if (arg.size() == 1 && arg[0] == name_mode[i])
			return init_mode(name_mode[i]);
	}
	return (NO_MODE);
}
