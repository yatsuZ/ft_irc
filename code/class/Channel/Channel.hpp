/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:03 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/19 16:35:54 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "./../../header/Ft_irc.hpp"

class Channel
{
public:
	~Channel();
	Channel(const std::string & n, const std::string & k);

	std::string get_name(void)const {return this->_name;}
	std::string	get_topic(void)const {return this->_topic;}

	void		set_name(const std::string & n){_name = n;}
private:
	std::string					_name;
	std::string					_key;
	std::string					_topic;
	// std::vector<Mode_Channel>	_mode; //?

	Channel();
};