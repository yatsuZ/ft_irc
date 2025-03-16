/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dcc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:43:13 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/16 18:19:03 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Dcc.hpp"

Dcc::Dcc():
_valide_dcc(false),
_type(IDK_DCC),
_file_name(""), 
_host(0), 
_port(0), 
_taille_du_fichier(0), 
_index_emeteur(-1), 
_index_recepteur(-1), 
_listen_fd(-1)
{
	// std::cout << GREEN << "default constructeur dcc" << NOCOLOR << std::endl;
}

Dcc::~Dcc()
{
	// std::cout << RED << "destructon dcc" << NOCOLOR << std::endl;
}

DCC_TOKEN 	Dcc::_init_type(std::string arg1)
{
	if (_valide_dcc == false)
		return (IDK_DCC);
	if (arg1 == "SEND")
		return (SEND_DCC);
	if (arg1 == "GET")
	{
		std::cout << RED << "GET DCC CMD " << NOCOLOR << std::endl;
		return (GET_DCC);
	}
	return (IDK_DCC);
}

std::string Dcc::_init_file_name(std::string arg2)
{
	if (_valide_dcc == false)
		return ("");
	return (arg2);
}

uint32_t	Dcc::_init_host(std::string arg3)
{
	if (_valide_dcc == false)
		return (0);
	// convertir un string en uint32_t
	bool error = false;
	uint32_t portl = ft_atol_limits(arg3, 0x00000000, 0xFFFFFFFF, &error);

	if (error)
		return (this->_valide_dcc = false, 0);
	
	
	return (static_cast<uint32_t>(portl));

}

uint16_t	Dcc::_init_port(std::string arg4)
{
	if (_valide_dcc == false)
		return (0);
	bool error = false;
	long portl = ft_atol_limits(arg4, 1, 65535, &error);
	
	if (error)
		return (this->_valide_dcc = false, 0);
	
	
	return (static_cast<uint16_t>(portl));
}

size_t		Dcc::_init_taille_du_fichier(std::string arg5)
{
	if (_valide_dcc == false)
		return (0);
	bool error = false;
	long file_size = ft_atol_limits(arg5, 1, 4294967295, &error);
		
	if (error)
		return (this->_valide_dcc = false, 0);
	
	return (static_cast<size_t>(file_size));
}

/////////


Dcc::Dcc(std::vector<std::string> split_param, ssize_t i_emeteur, ssize_t i_recpeteur):
_valide_dcc(								(split_param.size() == 6) ? (true): (false)),
_type(				_init_type				(_valide_dcc ? (split_param[1]) : (""))),
_file_name(			_init_file_name			(_valide_dcc ? (split_param[2]) : (""))), 
_host(				_init_host				(_valide_dcc ? (split_param[3]) : (""))), 
_port(				_init_port				(_valide_dcc ? (split_param[4]) : (""))), 
_taille_du_fichier(	_init_taille_du_fichier	(_valide_dcc ? (split_param[5]) : (""))), 
_index_emeteur(_valide_dcc == false || i_emeteur < 0 ? (-1) : (i_emeteur)), 
_index_recepteur(_valide_dcc == false || i_recpeteur < 0 ? (-1) : (i_recpeteur)), 
_listen_fd(-1)
{
	
	// std::cout << GREEN << "Constructeur parametric dcc " << i_emeteur << " " << i_recpeteur << NOCOLOR << std::endl;
	// std::cout << *this << std::endl;
}

/// @brief Si il a le meme information Alors return vrai
/// @param src le dcc qui est comparer avec l'actuel
/// @return bah si c'est vrai ou faux un bool quoi
bool Dcc::operator==(const Dcc & src) const
{
	return (
		get_type() == src.get_type() && 
		get_file_name() == src.get_file_name() && 
		// get_host() == src.get_host() && 
		// get_port() == src.get_port() && 
		get_taille_du_fichier() == src.get_taille_du_fichier() && 
		get_index_emeteur() == src.get_index_emeteur() && 
		get_index_recepteur() == src.get_index_recepteur()
	);
}

void Dcc::update_index(ssize_t i)
{
	if (i < 0)
		return ;
	if (i < _index_emeteur)
		--_index_emeteur;
	if (i < _index_recepteur)
		--_index_recepteur;
}

Dcc	& Dcc::operator=(Dcc const & rf)
{
	if (this != &rf)
	{
		_valide_dcc = rf.get_valide_dcc();
		_type = rf.get_type();
		_file_name = rf.get_file_name();
		_host = rf.get_host();
		_port = rf.get_port();
		_taille_du_fichier = rf.get_taille_du_fichier();
		_index_emeteur = rf.get_index_emeteur();
		_index_recepteur = rf.get_index_recepteur();
	}
	return (*this);

}

bool Dcc::is_my_send_request(const Dcc & src) const
{
	return (
		get_type() == GET_DCC && 
		src.get_type() == SEND_DCC &&
		get_file_name() == src.get_file_name() &&
		get_index_emeteur() == src.get_index_recepteur() &&
		get_index_recepteur() == src.get_index_emeteur()
	);
}
