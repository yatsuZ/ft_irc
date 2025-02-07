/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:44 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/07 00:55:54 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv/Irssi_serv.hpp"

Irssi_serv::Irssi_serv(std::string argv1, std::string argv2): Server(argv1, argv2)
{
	action_table[NO_ACTION] = &Irssi_serv::ft_no_action;
	action_table[ERROR_RECV_DATA] = &Irssi_serv::ft_error_recv_data;
	action_table[SHUTDOWN] = &Irssi_serv::ft_shutdown;
	action_table[DISCONNECT] = &Irssi_serv::ft_disconnect;
	action_table[CAP] = &Irssi_serv::ft_cap;
	action_table[NICK] = &Irssi_serv::ft_nick;
	action_table[USER] = &Irssi_serv::ft_user;
	action_table[MODE] = &Irssi_serv::ft_mode;
	action_table[PING] = &Irssi_serv::ft_ping;
	action_table[WHOIS] = &Irssi_serv::ft_whois;
	action_table[IDK] = &Irssi_serv::ft_idk;
}

Irssi_serv::~Irssi_serv()
{
}
