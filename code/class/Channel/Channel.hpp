/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:03 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/25 00:02:37 by yzaoui           ###   ########.fr       */
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

	std::string 				get_name(void)const {return this->_name;}
	std::string					get_key(void)const {return this->_key;}
	std::string					get_topic(void)const {return this->_topic;}
	std::vector<size_t>			get_index_users(void)const {return this->_index_users;}
	std::vector<size_t>			get_index_operators(void)const {return this->_index_operators;}
	size_t						get_nbr_of_user(void)const {return this->_nbr_user;}
	size_t						get_limit_user(void)const {return this->_limit_user;}
	std::vector<Mode>			get_mode(void)const {return this->_mode;}


	void		set_name(const std::string & n){_name = n;}
	void		set_topic(const std::string & t){_topic = t;}
	void		add_user(size_t idx_user);

	// erase
	void	errase_user(size_t index_user);
	void	update_index_of_user(size_t index_user);
	void	update_and_errase_index_of_user(size_t index_user);

private:
// cree un variable static le nombre dutilisateur actuelle
	std::string					_name;
	std::string					_key;
	std::string					_topic;
	std::vector<size_t> 		_index_users;
	std::vector<size_t>			_index_operators;
	size_t						_nbr_user;
	size_t						_limit_user;
	std::vector<Mode>	_mode; //?

	Channel();
};

std::ostream & operator<<(std::ostream & o, const Channel & c);
std::ostream & operator<<(std::ostream & o, std::vector<Channel> const & chanelle_list);
