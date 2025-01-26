/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:56 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 20:23:40 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../Server/Server.hpp"

class Irssi_serv: public Server
{
private:
	std::vector<Cmd_irssi>	link(pollfd &current_pollfd);

	//// ACTION du serveur

	void	connect(void);
	void	disconnect(size_t i, pollfd &current_pollfd);
	void	send_message(std::string message, pollfd &current_pollfd);

public:
	Irssi_serv(std::string argv1, std::string argv2): Server(argv1, argv2) {};
	void exec(void);

	~Irssi_serv();
};


