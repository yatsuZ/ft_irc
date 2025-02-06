/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:56 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/06 20:06:43 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../Server/Server.hpp"

class Irssi_serv: public Server
{
private:
	std::vector<Client>		_all_Client;
	std::vector<UserHuman>	_all_User;
	std::vector<Cmd_irssi>	link(pollfd &current_pollfd);
	
	Reaction_Serv	do_action(Cmd_irssi &cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd);


	//// ACTION du serveur
	Reaction_Serv		ft_no_action(Cmd_irssi &, pollfd &, size_t &);		// NO_ACTION
	Reaction_Serv		ft_error_recv_data(Cmd_irssi &, pollfd &, size_t &);// ERROR_RECV_DATA
	Reaction_Serv		ft_shutdown(Cmd_irssi &, pollfd &, size_t &);		// SHUTDOWN
	Reaction_Serv		ft_disconnect(Cmd_irssi &, pollfd &, size_t &);		// DISCONNECT
	Reaction_Serv		ft_cap(Cmd_irssi &, pollfd &, size_t &);			// CAP
	Reaction_Serv		ft_nick(Cmd_irssi &, pollfd &, size_t &);			// NICK
	Reaction_Serv		ft_user(Cmd_irssi &, pollfd &, size_t &);			// USER
	Reaction_Serv		ft_idk(Cmd_irssi &, pollfd &, size_t &);			// IDK dernier

	typedef Reaction_Serv (Irssi_serv::*MethodeActionIrc)(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd);
	MethodeActionIrc action_table[IDK + 1];

	// OTHER
	void	connect(void);
	int		send_message(std::string message, pollfd &current_pollfd);

	Client		* _get_client_by_index_of_pollfd(ssize_t i);
	UserHuman	* _get_userhuman_by_index_of_pollfd(ssize_t i);

public:
	Irssi_serv(std::string argv1, std::string argv2);
	void exec(void);

	~Irssi_serv();
};


