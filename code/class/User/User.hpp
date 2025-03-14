/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:00:12 by kuro              #+#    #+#             */
/*   Updated: 2025/03/14 01:13:34 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Ft_irc.hpp"
#include "./../Channel/Channel.hpp"

class Channel;
class User
{
protected:
	std::string		_nick;
	std::string		_name;
	std::string 	_hostname;
	std::string		_real_name;
	std::string		_servername;
	std::string		_msg_leave;
	Mode			_mode;
	int				_is_init;

	// std::vector<Channel>	_channels; //modifier en ptr de chan
	std::vector<size_t>		_chans;	//tableau d'index de channels
public:
	User();
	~User();
	User(std::string & nick);

	void		set_nick(const std::string &);
	void		set_name(const std::string &);
	void		set_hostname(const std::string &);
	void		set_servername(const std::string &);
	void		set_msg_leave(const std::string & new_msg) {this->_msg_leave = new_msg;}
	void		set_Realname(const std::string &);
	void		set_mode(Mode newmode);
	void		add_chan(size_t idx_of_chan);

	std::string				get_nick() 			const {return this->_nick;}
	std::string				get_name() 			const {return this->_name;}
	std::string				get_hostname()		const {return this->_hostname;}
	std::string				get_realname()		const {return this->_real_name;}
	std::string				get_servername()	const {return this->_servername;}
	std::string				get_msg_leave()		const {return this->_msg_leave;}
	Mode					get_mode()			const {return this->_mode;}
	bool					get_Set_User() 		const {return (_is_init == 2 || _is_init == -1);}
	bool					get_Set_Nick()		const {return (_is_init == 1 || _is_init == -1);}
	bool					get_is_init()		const {return (_is_init == -1);}
	std::vector<size_t>		get_chans()			const {return this->_chans;}

	std::string				list_mode()const;
	std::string				mode_to_str(const Mode & m)const;

	// erase
	void	erase_mode(Mode newmode);
	void	errase_chan(size_t index_chan);
	void	update_index_of_chan(size_t index_chan);
	void	update_and_errase_index_of_chan(size_t index_chan);

};

std::ostream & operator<<( std::ostream & o, User const & user);
