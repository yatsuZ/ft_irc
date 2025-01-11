/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 22:24:46 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/10 23:05:40 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"

class User
{
private:
	static unsigned long	_nbr_of_user;    // Variable statique pour gérer les IDs
	static unsigned long	_nextId;         // Variable statique pour gérer les IDs
	unsigned long			_id;             // ID unique de l'utilisateur
	int						_fd;             // Descripteur de fichier du client
	sockaddr_in				_address;        // Adresse du client
	socklen_t				_address_len;    // Taille de l'adresse
	std::string				_username;       // Nom d'utilisateur

	User();
public:
	User(int fd, sockaddr_in address, socklen_t	address_len, std::string _username);
	~User();
};



/// @brief Affiche tout les attributs de la class user
std::ostream & operator<<( std::ostream & o, User const & user);
