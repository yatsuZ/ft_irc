/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:05:48 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/12 19:39:35 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"

class Client
{
private:
	static unsigned long	_nextId;               // Variable statique pour gérer les IDs
	static unsigned long	_nbr_of_client;        // Variable statique pour gérer le nombre de client

	const unsigned long		_id;                   // ID unique de l'utilisateur
	int						_fd;                   // Descripteur de fichier du client
	long					_index_client_pollfd;  // Pollfd du client
	sockaddr_in				_address;              // Adresse du client
	socklen_t				_address_len;          // Taille de l'adresse
	Client();
public:
	Client(Client const &src);
	Client	&operator=(Client const &src);
	Client(int fd, long index_client_pollfd, sockaddr_in address, socklen_t address_len);
	~Client();

	unsigned long			get_nextId() const {return this->_nextId;}
	unsigned long			get_nbr_of_client() const {return this->_nbr_of_client;}

	unsigned long			get_id() const {return this->_id;}
	long					get_index_client_pollfd() const {return this->_index_client_pollfd;};  // Pollfd du client
	int						get_fd() const {return this->_fd;}
	sockaddr_in				get_address() const {return this->_address;}
	socklen_t				get_address_len() const {return this->_address_len;}

	void					set_index_client_pollfd(long new_index_client_pollfd){ this->_index_client_pollfd = new_index_client_pollfd;}
	void					set_fd(int new_fd){ this->_fd = new_fd;}
	void					disconnect(void);
};

/// @brief Affiche tout les attributs de la class client
std::ostream & operator<<( std::ostream & o, Client const & client);
