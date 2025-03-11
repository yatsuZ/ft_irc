/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:36:17 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/11 16:41:39 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include "./../../header/Ft_irc.hpp"
#include "./User/User.hpp"

class	Bot
{
private:
	std::string	_name;

public:
	Bot(std::string & n);
	~Bot();

	std::string	get_name(void)const{return  _name;}

	void		set_name(const std::string & n){ _name = n;}

	void		bad_words()
};