/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:56 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/06 17:43:48 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../Server/Server.hpp"
// #include "./../Channel/Channel.hpp"

// class	Channel;

class Irssi_serv: public Server
{
private:
	std::vector<UserHuman>		_all_User;
	std::vector<Channel>		_all_Channel;			// liste des channels existants

	// Execution
	std::vector<Cmd_irssi>		link(pollfd &current_pollfd);
	
	Reaction_Serv	do_action(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd);


	//// ACTION du serveur
	Reaction_Serv		ft_no_action(Cmd_irssi &, UserHuman *, pollfd &, size_t &);			// NO_ACTION
	Reaction_Serv		ft_error_recv_data(Cmd_irssi &, UserHuman *, pollfd &, size_t &);	// ERROR_RECV_DATA
	Reaction_Serv		ft_shutdown(Cmd_irssi &, UserHuman *, pollfd &, size_t &);			// SHUTDOWN
	Reaction_Serv		ft_disconnect(Cmd_irssi &, UserHuman *, pollfd &, size_t &);		// DISCONNECT
	Reaction_Serv		ft_cap(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// CAP
	Reaction_Serv		ft_nick(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// NICK
	Reaction_Serv		ft_user(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// USER
	Reaction_Serv		ft_mode(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// MODE
	Reaction_Serv		ft_ping(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// PING
	Reaction_Serv		ft_whois(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// WHOIS
	Reaction_Serv		ft_quit(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// QUIT
	Reaction_Serv		ft_join(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// JOIN
	Reaction_Serv		ft_privmsg(Cmd_irssi &, UserHuman *, pollfd &, size_t &);			// PRIVMSG
	// Reaction_Serv		ft_who(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// WHO
	Reaction_Serv		ft_idk(Cmd_irssi &, UserHuman *, pollfd &, size_t &);				// IDK dernier


	typedef Reaction_Serv (Irssi_serv::*MethodeActionIrc)(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd);
	MethodeActionIrc action_table[IDK + 1];
	
	//MODE

	typedef Mode (Irssi_serv::*MethodeModeIrc)(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, Channel *curent_chan);
	MethodeModeIrc	mode_table[NO_MODE + 1];

	Mode		init_mode(char & c);
	Mode		get_mode(std::string & arg);

	Mode		ft_mode_i(Cmd_irssi &, UserHuman * , pollfd &, Channel *);
	Mode		ft_mode_t(Cmd_irssi &, UserHuman * , pollfd &, Channel *);
	Mode		ft_mode_k(Cmd_irssi &, UserHuman * , pollfd &, Channel *);
	Mode		ft_mode_o(Cmd_irssi &, UserHuman * , pollfd &, Channel *);
	Mode		ft_mode_l(Cmd_irssi &, UserHuman * , pollfd &, Channel *);
	Mode		ft_mode_none(Cmd_irssi &, UserHuman * , pollfd &, Channel *);

	void		do_mode(Cmd_irssi &,  UserHuman *, pollfd &, Channel *);
	// OTHER
	void	connect(void);
	bool	_nick_already_used(std::string nick) const;
	void	_send_message_to_a_chanelle(UserHuman &emeteur, Channel &chan, const std::string msg, bool only_op = false);
	void	_send_message_to_a_all_chanelle(UserHuman &emeteur, const std::string msg);

	// specefique get
	UserHuman	* _get_userhuman_by_index_of_pollfd(ssize_t i);
	UserHuman	* _get_userhuman_by_nick(const std::string & nick);
	Channel		* _get_channel_by_name(const std::string & name);
	ssize_t 	_get_index_of_userhuman_by_nick(const std::string & nick);
	ssize_t		_get_index_channel_by_name(const std::string & name);

	Channel * _find_chan_in_user_by_name(UserHuman & emeteur, std::string & name_chan);
	// LIST
	std::string get_all_chan_name_from_user(const UserHuman & user);
	std::string get_all_nick_from_chan(const Channel & chan);
	std::string get_all_user_nick_from_chan(const Channel & chan);

	// errase element

	void	_errase_chan_by_index_from_tab(size_t index_of_chan);
	void	_errase_user_by_index_from_tab(size_t index_of_user);
	void	_erase_empty_chanelle(void);
	void	_errase_user_from_tab(pollfd &current_pollfd);


	// debug
	void		show_all_chan_from_user(const UserHuman & user){std::cout << BLUE + user.get_nick() + PINK << " all his chanelle : " << GREEN + get_all_chan_name_from_user(user) << NOCOLOR << std::endl;}
	void		show_all_user_from_chanelle(const Channel & chan){std::cout << GREEN + chan.get_name() + PINK << " all his user : " << BLUE + get_all_nick_from_chan(chan) << NOCOLOR << std::endl;}

public:
	Irssi_serv(std::string argv1, std::string argv2);
	void exec(void);

	~Irssi_serv();
};


