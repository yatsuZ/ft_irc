/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/02/06 19:59:09 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

class User
{
protected:
	std::string		_nick;
	std::string		_name;
	std::string 	_hostname;
	std::string		_realname;		
	std::string		_servername;
public:
	User();
	~User();
	User(std::string & nick);

	void		setNick(const std::string &);
	void		setName(const std::string &);
	void		setHostname(const std::string &);
	void		setServername(const std::string &);
	void		setRealname(const std::string &);

	std::string	getNick();
	std::string	getName();
	std::string	getHostname();
	std::string	getRealname();
	std::string	getServername();

};

std::ostream & operator<<( std::ostream & o, User const & user);
