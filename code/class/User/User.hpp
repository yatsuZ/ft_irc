/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/02/16 17:40:57 by yzaoui           ###   ########.fr       */
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

	void		set_nick(const std::string &);
	void		set_name(const std::string &);
	void		set_hostname(const std::string &);
	void		set_servername(const std::string &);
	void		set_Realname(const std::string &);
	void		set_mode(void);

	std::string	get_nick() 			const {return this->_nick;}
	std::string	get_name() 			const {return this->_name;}
	std::string	get_hostname()		const {return this->_hostname;}
	std::string	get_realname()		const {return this->_real_name;}
	std::string	get_servername()	const {return this->_servername;}
	Mode_User	get_droituser()		const {return this->_droit_user;}
	bool		get_Set_User() 		const {return (_is_init == 2 || _is_init == -1);}
	bool		get_Set_Nick()		const {return (_is_init == 1 || _is_init == -1);}
	bool		get_is_init()		const {return (_is_init == -1);}
	bool		getMode()			const {return this->_mode;}
};

std::ostream & operator<<( std::ostream & o, User const & user);
std::ostream & operator<<( std::ostream & o, Mode_User const modeu);
