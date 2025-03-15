/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dcc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:43:21 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/15 21:21:02 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Ft_irc.hpp"

class UserHuman;

enum DCC_TOKEN {
	SEND_DCC,
	GET_DCC,
	IDK_DCC
};

class Dcc
{
private:

	bool		_valide_dcc;
	DCC_TOKEN	_type;
	std::string	_file_name;
	uint32_t	_host;
	uint16_t	_port;
	size_t		_taille_du_fichier;
	ssize_t		_index_emeteur;
	ssize_t		_index_recepteur;
	std::string	_msg_err;
	Dcc();
	
	DCC_TOKEN 	_init_type(std::string);
	std::string _init_file_name(std::string);
	uint32_t	_init_host(std::string);
	uint16_t	_init_port(std::string);
	size_t		_init_taille_du_fichier(std::string);

public:
	Dcc(std::vector<std::string>, ssize_t , ssize_t);
	~Dcc();

	bool 		get_valide_dcc()		const {return _valide_dcc;}
	DCC_TOKEN 	get_type()				const {return _type;}
	std::string get_file_name()			const {return _file_name;}
	uint32_t	get_host()				const {return _host;}
	uint16_t	get_port()				const {return _port;}
	size_t		get_taille_du_fichier()	const {return _taille_du_fichier;}
	ssize_t		get_index_emeteur()		const {return _index_emeteur;}
	ssize_t		get_index_recepteur()	const {return _index_recepteur;}
	std::string	get_msg_err()			const {return _msg_err;}
	bool		operator==(const Dcc & src) const;

	void		update_index(ssize_t);
};

std::ostream & operator<<( std::ostream & o, Dcc const & dcc);
std::ostream & operator<<( std::ostream & o, DCC_TOKEN const & dcc_token);
std::ostream & operator<<( std::ostream & o, std::vector<Dcc> const & list_dcc);
