/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:56 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 23:23:04 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../Server/Server.hpp"

class Irssi_serv: public Server
{
private:
	std::vector<Cmd_irssi>	link(pollfd &current_pollfd);
	
	Reaction_Serv	do_action(Cmd_irssi &cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd);


	//// ACTION du serveur
	Reaction_Serv		ft_no_action(Cmd_irssi &, pollfd &, size_t &);		// NO_ACTION
	Reaction_Serv		ft_error_recv_data(Cmd_irssi &, pollfd &, size_t &);// ERROR_RECV_DATA
	Reaction_Serv		ft_shutdown(Cmd_irssi &, pollfd &, size_t &);		// SHUTDOWN
	Reaction_Serv		ft_disconnect(Cmd_irssi &, pollfd &, size_t &);		// DISCONNECT
	Reaction_Serv		ft_idk(Cmd_irssi &, pollfd &, size_t &);			// IDK dernier

	typedef Reaction_Serv (Irssi_serv::*MethodeActionIrc)(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd);
	MethodeActionIrc action_table[IDK + 1];

	// OTHER

	void	connect(void);
	int		send_message(std::string message, pollfd &current_pollfd);

public:
	Irssi_serv(std::string argv1, std::string argv2);
	void exec(void);

	~Irssi_serv();
};


