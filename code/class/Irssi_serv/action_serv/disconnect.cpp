/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:22:31 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/27 15:51:24 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/// @brief Quand pc se deconnecte aux serveur
Reaction_Serv	Irssi_serv::ft_disconnect(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_user;
	(void)	current_cmd;
	std::cout << RED << "◐◐◐◐◐◐◐◐◐◐◐ DISCONNECT ◑◑◑◑◑◑◑◑◑◑◑" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd<< NOCOLOR << std::endl;// surpimer le client
	
	this->_errase_user_from_tab(current_pollfd);
	this->_all_pollfd.erase(this->_all_pollfd.begin() + index_of_current_pollfd);
	close(current_pollfd.fd);

	// std::cout << this->_all_pollfd << std::endl;
	std::cout << RED << "◐◐◐◐◐◐◐◐◐◐◐ END DISCONNECT ◑◑◑◑◑◑◑◑◑◑◑" << NOCOLOR << std::endl;// surpimer le client
	std::cout << this->_all_User << std::endl;

	index_of_current_pollfd--;
	return (PASS_SERV);
}
