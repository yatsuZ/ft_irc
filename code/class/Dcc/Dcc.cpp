/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dcc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:43:13 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/14 01:05:17 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Dcc.hpp"

Dcc::Dcc()
{
	std::cout << GREEN << "default constructeur dcc" << NOCOLOR << std::endl;
}

Dcc::~Dcc()
{
	std::cout << RED << "destructon dcc" << NOCOLOR << std::endl;
}

DCC_TOKEN 	Dcc::_init_type(std::string arg1)
{
	if (_valide_dcc == false)
		return (IDK_DCC);
	if (arg1 == "SEND")
		return (SEND_DCC);
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


Dcc::Dcc(std::vector<std::string> split_param, UserHuman * emeteur, UserHuman * recepteur):
_valide_dcc(								(split_param.size() == 6) ? (true): (false)),
_type(				_init_type				(_valide_dcc ? (split_param[1]) : (""))),
_file_name(			_init_file_name			(_valide_dcc ? (split_param[2]) : (""))), 
_host(				_init_host				(_valide_dcc ? (split_param[3]) : (""))), 
_port(				_init_port				(_valide_dcc ? (split_param[4]) : (""))), 
_taille_du_fichier(	_init_taille_du_fichier	(_valide_dcc ? (split_param[5]) : (""))), 
_emeteur(emeteur), 
_recepteur(recepteur)
{
	std::cout << GREEN << "Constructeur parametric dcc" << NOCOLOR << std::endl;
	std::cout << *this << std::endl;
}
