/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:48 by kuro              #+#    #+#             */
/*   Updated: 2025/02/16 17:51:00 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(): _index_pollfd(-1)
{
	// std::cout << "Client attempting to connect..." << std::endl;
}

Client::Client(ssize_t index_pollfd, sockaddr_in client_addr, socklen_t client_len):
_index_pollfd(index_pollfd),
_client_addr(client_addr),
_client_len(client_len),
_is_connect(true)
{
	// std::cout << "Client attempting to connect..." << std::endl;
}

Client::Client(Client const & src):
_index_pollfd(src.get_index_pollfd()),
_client_addr(src.get_client_addr()),
_client_len(src.get_client_len()),
_is_connect(src.get_is_connect())
{
}

Client::~Client(){}

std::string	Client::get_ip_to_string(void) const
{
	char ip_buffer[INET_ADDRSTRLEN];  // Taille max pour une IPv4
	if (inet_ntop(AF_INET, &(this->_client_addr.sin_addr), ip_buffer, INET_ADDRSTRLEN) == NULL)
		return "Unknown"; // Gestion d'erreur

	return std::string(ip_buffer);
}


uint16_t	Client::get_port(void) const
{
	return ntohs(this->_client_addr.sin_port);
}


std::string	Client::get_port_to_string(void) const
{
	std::ostringstream oss;
	oss << ntohs(this->_client_addr.sin_port);
	return oss.str();
}
