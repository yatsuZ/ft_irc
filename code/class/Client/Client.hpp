/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:05:48 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/11 00:01:58 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"

class Client
{
private:
	static unsigned long	_nextId;         // Variable statique pour gérer les IDs
	static unsigned long	_nbr_of_client;  // Variable statique pour gérer le nombre de client
	const unsigned long		_id;             // ID unique de l'utilisateur
	int						_fd;             // Descripteur de fichier du client
	sockaddr_in				_address;        // Adresse du client
	socklen_t				_address_len;    // Taille de l'adresse

	Client();
public:
	Client(int fd, sockaddr_in address, socklen_t address_len);
	~Client();

	unsigned long			getid() const {return this->_id;}
	int						getfd() const {return this->_fd;}
	sockaddr_in				getaddress() const {return this->_address;}
	socklen_t				getaddress_len() const {return this->_address_len;}
};



/// @brief Affiche tout les attributs de la class client
std::ostream & operator<<( std::ostream & o, Client const & client);
