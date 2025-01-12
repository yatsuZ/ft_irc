/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:05:55 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/12 20:24:09 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Server/Server.hpp"

// Initialisation de la variable statique
unsigned long Client::_nextId = 0;
unsigned long Client::_nbr_of_client = 0;

Client::Client():
_id(this->_nextId++),
_fd(-1),
_address(),
_address_len(0)
{
	std::cout << getColorCode(YELLOW) << "Constructeur d'un Client" << getColorCode(NOCOLOR) << std::endl;
	this->_nbr_of_client++;
}

Client::Client(Client const &src):
_id(src.get_id()),
_fd(src.get_fd()),
_index_client_pollfd(src.get_index_client_pollfd()),
_address(src.get_address()),
_address_len(src.get_address_len())
{
	this->_nbr_of_client++;
	std::cout << getColorCode(MAGENTA) << "Constructeur PAR COPY d'un Client" << getColorCode(NOCOLOR) << std::endl;
	*this = src;
}

Client	&Client::operator=(Client const &src)
{
	if (this != &src)
	{
		this->_fd = src.get_fd();
		this->_index_client_pollfd = src.get_index_client_pollfd();
		this->_address = src.get_address();
		this->_address_len = src.get_address_len();
	}
	return (*this);
}


Client::~Client()
{
	std::cout << getColorCode(RED) << "Deconstructeur d'un Client" << getColorCode(NOCOLOR) << std::endl;
	// this->disconnect();
	this->_nbr_of_client--;
}

Client::Client(int fd, long index_client_pollfd, sockaddr_in address, socklen_t address_len):
_id(this->_nextId++),
_fd(fd),
_index_client_pollfd(index_client_pollfd),
_address(address),
_address_len(address_len)
{
	this->_nbr_of_client++;
	std::cout << getColorCode(GREEN) << "Constructeur d'un Client" << getColorCode(NOCOLOR) << std::endl;
}

void	Client::disconnect(void)
{
	if (this->_fd >= 0)
		close(this->_fd);
	this->_fd = -1;
}

std::ostream & operator<<( std::ostream & o, Client const & client)
{
	sockaddr_in const &adresse_client = client.get_address();
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &adresse_client.sin_addr, ip_str, INET_ADDRSTRLEN);

	o << "|" << " ";
	o << getColorCode(GREEN) << client.get_id() << getColorCode(NOCOLOR) << " " << "|" << " ";
	o << getColorCode(CYAN) << client.get_fd() << getColorCode(NOCOLOR) << " " << "|" << " ";
	o << getColorCode(BLUE) << ip_str << getColorCode(NOCOLOR) << ":" << getColorCode(BLUE) << ntohs(adresse_client.sin_port) << getColorCode(NOCOLOR) << " " << "|" << " ";
	o << getColorCode(YELLOW) << client.get_address_len() << getColorCode(NOCOLOR) << " " << "|";

	return o;
}