/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:03 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/21 19:46:20 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "./../../header/Ft_irc.hpp"
#include "./../User/User.hpp"

class User;

class Channel
{
public:
	~Channel();
	Channel(const std::string & n, const std::string & k);

	std::string get_name(void)const {return this->_name;}
	std::string	get_topic(void)const {return this->_topic;}

	void		set_name(const std::string & n){_name = n;}
	void		set_topic(const std::string & t){_topic = t;}
	void		add_user(size_t idx_user);
	
private:
	std::string					_name;
	std::string					_key;
	std::string					_topic;
	std::vector<size_t> 		_users;
	size_t						_limit_user;

	std::vector<User>			_operators;
	// std::vector<Mode_Channel>	_mode; //?

	Channel();
};