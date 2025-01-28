/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/01/28 01:09:25 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../header/Ft_irc.hpp"

class User
{
public:
	User();
	~User();

	void		setNick(const std::string & n);
	std::string	getNick();

private:
	std::string	_nick;
	std::vector<std::string> chanId; //tableau de chanID

};