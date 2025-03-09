/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:55:03 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/09 17:17:05 by smlamali         ###   ########.fr       */
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
	std::string					get_autor_topic(void)const {return this->_autor_topic;}
	time_t						get_creation_topic(void)const {return this->_creation_topic;}
	std::vector<size_t>			get_index_users(void)const {return this->_index_users;}
	std::vector<size_t>			get_index_operators(void)const {return this->_index_operators;}
	size_t						get_nbr_of_user(void)const {return this->_nbr_user;}
	size_t						get_limit_user(void)const {return this->_limit_user;}


	void		set_name(const std::string & n){_name = n;}
	void		set_topic(const std::string & t){_topic = t;}
	void		set_mode(Mode m);
	void		set_operator(size_t idx_user){_index_operators.push_back(idx_user);}
	void		set_limit(std::string l);
	void		set_key(std::string k) {_key = k;}
	void		set_autor_topic(const std::string & at){_autor_topic = at;}
	void		set_creation_topic(const time_t & ct){_creation_topic = ct;}
	void		add_user(size_t idx_user);
	std::string	time_creation_in_string(void) const;

	bool		is_operator(size_t idx_user) const;
	bool		is_in_chan(size_t idx_user);
	std::string	list_mode(void)const;
	std::string	mode_to_str(const Mode & m)const;


	// erase
	void	erase_mode(Mode m);
	void	errase_user(size_t index_user);
	void	update_index_of_user(size_t index_user);
	void	update_and_errase_index_of_user(size_t index_user);

private:
// cree un variable static le nombre dutilisateur actuelle
	std::string					_name;
	std::string					_key;
	std::string					_topic;
	std::string					_autor_topic;
	time_t						_creation_topic;
	std::vector<size_t> 		_index_users;
	std::vector<size_t>			_index_operators;
	size_t						_nbr_user;
	size_t						_limit_user;
	std::vector<Mode>			_mode; 

	Channel();
};

std::ostream & operator<<(std::ostream & o, const Channel & c);
std::ostream & operator<<(std::ostream & o, std::vector<Channel> const & chanelle_list);
