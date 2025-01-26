/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:56 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 22:07:44 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../Server/Server.hpp"

class Irssi_serv: public Server
{
private:
	std::vector<Cmd_irssi>	link(pollfd &current_pollfd);
	
	int	do_action(Cmd_irssi &cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd);


	//// ACTION du serveur
	int		ft_no_action(Cmd_irssi &, pollfd &, size_t &);		// NO_ACTION
	int		ft_error_recv_data(Cmd_irssi &, pollfd &, size_t &);// ERROR_RECV_DATA
	int		ft_shutdown(Cmd_irssi &, pollfd &, size_t &);		// SHUTDOWN
	int		ft_disconnect(Cmd_irssi &, pollfd &, size_t &);		// DISCONNECT
	int		ft_idk(Cmd_irssi &, pollfd &, size_t &);			// IDK dernier

	typedef int (Irssi_serv::*MethodeActionIrc)(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd);
	MethodeActionIrc action_table[IDK + 1];

	// OTHER

	void	connect(void);
	int		send_message(std::string message, pollfd &current_pollfd);

public:
	Irssi_serv(std::string argv1, std::string argv2);
	void exec(void);

	~Irssi_serv();
};


