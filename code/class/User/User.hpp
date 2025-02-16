/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/02/16 12:46:11 by yzaoui           ###   ########.fr       */
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
	Mode_User		_droit_user;
	bool			_mode;
	int				_is_init;

public:
	User();
	~User();
	User(std::string & nick);

	void		setNick(const std::string &);
	void		setName(const std::string &);
	void		setHostname(const std::string &);
	void		setServername(const std::string &);
	void		setRealname(const std::string &);
	void		setMode(void);
	
	std::string	getNick() 		const {return this->_nick;}
	std::string	getName() 		const {return this->_name;}
	std::string	getHostname()	const {return this->_hostname;}
	std::string	getRealname()	const {return this->_real_name;}
	std::string	getServername()	const {return this->_servername;}
	bool		getSet_User() 	const {return (_is_init == 2 || _is_init == -1);}
	bool		getSet_Nick()	const {return (_is_init == 1 || _is_init == -1);}
	bool		getMode()		const {return this->_mode;}
};

std::ostream & operator<<( std::ostream & o, User const & user);
