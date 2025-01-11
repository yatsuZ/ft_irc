/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:05:55 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/11 00:30:05 by yzaoui           ###   ########.fr       */
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

Client::~Client()
{
	std::cout << getColorCode(YELLOW) << "Deconstructeur d'un Client" << getColorCode(NOCOLOR) << std::endl;
	this->_nbr_of_client--;
}


Client::Client(int fd, sockaddr_in address, socklen_t address_len):
_id(this->_nextId++),
_fd(fd),
_address(address),
_address_len(address_len)
{
	this->_nbr_of_client++;
	std::cout << getColorCode(GREEN) << "Constructeur d'un Client" << getColorCode(NOCOLOR) << std::endl;
}

std::ostream & operator<<( std::ostream & o, Client const & client)
{
	sockaddr_in const &adresse_client = client.getaddress();
	char ip_str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &adresse_client.sin_addr, ip_str, INET_ADDRSTRLEN);

	o << "|" << " ";
	o << getColorCode(GREEN) << client.getid() << getColorCode(NOCOLOR) << " " << "|" << " ";
	o << getColorCode(CYAN) << client.getfd() << getColorCode(NOCOLOR) << " " << "|" << " ";
	o << getColorCode(BLUE) << ip_str << getColorCode(NOCOLOR) << ":" << getColorCode(BLUE) << ntohs(adresse_client.sin_port) << getColorCode(NOCOLOR) << " " << "|" << " ";
	o << getColorCode(YELLOW) << client.getaddress_len() << getColorCode(NOCOLOR) << " " << "|";

	return o;
}