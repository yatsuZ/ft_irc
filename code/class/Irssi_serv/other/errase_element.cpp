/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errase_element.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 23:23:51 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/25 00:42:56 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

void	Irssi_serv::_errase_user_from_tab(pollfd &current_pollfd)
{
	std::cout << "All user/client :" << std::endl;

	bool find_user_associate_by_pollfd = false;
	size_t index_of_user = 0;
	for (std::vector<UserHuman>::iterator iteration_user = this->_all_User.begin();
	iteration_user != this->_all_User.end(); iteration_user++)
	{
		index_of_user++;
		ssize_t index_pollfd = iteration_user->get_index_pollfd();
		if (index_pollfd != -1 && current_pollfd.fd == this->_all_pollfd[index_pollfd].fd)
		{
			std::cout << RED << "Client to erase :\t" << NOCOLOR << static_cast<Client>(*iteration_user) << std::endl;//modifier laffichage
			_errase_user_by_index_from_tab(index_of_user);
			iteration_user = this->_all_User.erase(iteration_user);
			if (iteration_user == this->_all_User.end())
				break ;
			find_user_associate_by_pollfd = true;
		}
		if (find_user_associate_by_pollfd)
			iteration_user->set_index_pollfd(iteration_user->get_index_pollfd() - 1);
		std::cout << "\t- " << static_cast<Client>(*iteration_user) << std::endl;
	}
}

// Suprime le chanelle puis mets a jour tout les utilisateur
void	Irssi_serv::_errase_chan_by_index_from_tab(size_t index_of_chan)
{
	std::cout << "debut de la supression du chanelle " << _all_Channel[index_of_chan] << std::endl;


	std::vector<size_t> all_user_from_this_chan = _all_Channel[index_of_chan].get_index_users();
	for (std::vector<size_t>::iterator i = all_user_from_this_chan.begin(); i != all_user_from_this_chan.end(); i++)
	{
		this->_all_User[*i].update_and_errase_index_of_chan(index_of_chan);
	}
	
	std::vector<Channel>::iterator chan_to_delet = this->_all_Channel.begin();
	for (size_t i = 0; i < index_of_chan; i++)
	{
		chan_to_delet++;
		if (chan_to_delet == this->_all_Channel.end())
			return ;
	}
	this->_all_Channel.erase(chan_to_delet);

	// Metre un message si on shouaite dire qun chanelle est suprimer
	std::cout << "Supression fini" << std::endl;
}

// Suprime le user puis mets a jour tout les chanelle
void	Irssi_serv::_errase_user_by_index_from_tab(size_t index_of_user)
{
	std::cout << "Supression du user, les chanelle doit etre mis a jour";
	show_all_chan_from_user(_all_User[index_of_user]);


	std::vector<size_t> all_chan_from_this_user = _all_User[index_of_user].get_chans();
	for (std::vector<size_t>::iterator i = all_chan_from_this_user.begin(); i != all_chan_from_this_user.end(); i++)
	{
		this->_all_Channel[*i].update_and_errase_index_of_user(index_of_user);
	}

	std::vector<UserHuman>::iterator user_to_delet = this->_all_User.begin();
	for (size_t i = 0; i < index_of_user; i++)
	{
		user_to_delet++;
		if (user_to_delet == this->_all_User.end())
			return ;
	}
	// this->_all_User.erase(user_to_delet);

	// Metre un message si on shouaite dire qun user est suprimer
	std::cout << "les chnaelle sont mis a jour" << std::endl;
}
