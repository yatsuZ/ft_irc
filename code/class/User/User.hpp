/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/02/11 19:24:56 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

class User
{
protected:
	std::string		_nick;
	std::string		_name;
	std::string 	_hostname;
	std::string		_real_name;
	std::string		_servername;
	Mode			_droit_user;
	bool			_set_user;

public:
	User();
	~User();
	User(std::string & nick);

	void		setNick(const std::string &);
	void		setName(const std::string &);
	void		setHostname(const std::string &);
	void		setServername(const std::string &);
	void		setRealname(const std::string &);
	void		setting_User(void){this->_set_user = true;}

	std::string	getNick() 		const {return this->_nick;}
	std::string	getName() 		const {return this->_name;}
	std::string	getHostname()	const {return this->_hostname;}
	std::string	getRealname()	const {return this->_real_name;}
	std::string	getServername()	const {return this->_servername;}
	bool		getSet_User() 	const {return this->_set_user;}

};

std::ostream & operator<<( std::ostream & o, User const & user);
