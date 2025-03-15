/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:45 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/15 22:49:41 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./UserHuman.hpp"

UserHuman::UserHuman(void): User(), Client(), _step_of_link(0)
{
}

UserHuman::UserHuman(std::string & nick, Client & client): User(nick), Client(client), _step_of_link(0)
{
	// std::cout << "User Human \"" << PINK << nick << NOCOLOR << "\" is joining" << std::endl;
}


UserHuman::UserHuman(Client & client): User(), Client(client), _step_of_link(0)
{
	// std::cout << "User Human \"" << PINK << this->get_name() << NOCOLOR << "\" is joining" << std::endl;
}

UserHuman::~UserHuman(){}

void	UserHuman::get_welcolm(const std::string & server_name, Action from_this_action, pollfd &pollfd)
{
	if (_is_init == -1)
		return;
	else if (from_this_action == NICK && _is_init != -1 && _is_init != 1)
		_is_init += 1;
	else if (from_this_action == USER && _is_init != -1 && _is_init != 2)
		_is_init += 2;
	if (_is_init == 3)
	{
		send_message(RPL_WELCOME(server_name, get_nick(), get_name(), get_ip_to_string()), pollfd);
		send_message(RPL_YOURHOST(server_name, get_nick(), "<" + CYAN + "Yassine " + PINK + "Samira " + YELLOW +"Côme"+NOCOLOR+"> 0.1"), pollfd);
		_is_init = -1;
	}
}

void	UserHuman::get_msg_by_step(const std::string & server_name, pollfd &pollfd)
{
	if (_step_of_link == 0)
	{
		send_message(NOTICE(server_name, get_nick(), "We verify your nickname and user and the password ..."), pollfd);
		_step_of_link++;
	}
}

bool	UserHuman::add_request_send_file(Dcc new_request_send)
{
	// verifier qu'il n'y a pas plusieur fois la meme requette
	for (size_t i = 0; i < this->_all_request_to_send_files.size(); i++)
	{
		if (new_request_send == this->_all_request_to_send_files[i])
		{
			std::cout << "IL y a deja la meme requete" << std::endl;
			return (false);
		}
	}
	std::cout << "Nouvelle requete" << std::endl;
	this->_all_request_to_send_files.push_back(new_request_send);
	return (true);
}

void	UserHuman::update_index_dcc(ssize_t index_to_del)
{
	std::cout << "Je mets a jour les index de mes requette dcc" << std::endl;
	for (size_t i = 0; i < this->_all_request_to_send_files.size(); i++)
	{
		this->_all_request_to_send_files[i].update_index(index_to_del);
	}
}

Dcc UserHuman::pop_request_dcc(Dcc & get_request)
{
	Dcc res;
	for (std::vector<Dcc>::iterator i_r_dcc = this->_all_request_to_send_files.begin(); i_r_dcc != this->_all_request_to_send_files.end(); i_r_dcc++)
	{
		if (get_request.is_my_send_request(*i_r_dcc))
		{
			res = *i_r_dcc;
			_all_request_to_send_files.erase(i_r_dcc);
			std::cout << "Supression d'un request send" << std::endl;
			return (res);
		}
	}
	return (res);
}