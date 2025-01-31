/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/01/31 01:20:39 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

class User
{
protected:
	std::string				_name;
	std::string				_nick;
public:
	User();
	User(std::string & name);
	~User();

	void		setNick(const std::string &);
	std::string	getNick();
	void		setName(const std::string &);
	std::string	getName();

};

std::ostream & operator<<( std::ostream & o, User const & user);
