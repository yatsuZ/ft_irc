/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irssi_serv.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:05:44 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/27 13:50:34 by smlamali         ###   ########.fr       */
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
	action_table[WHOWAS] = &Irssi_serv::ft_whowas;
	action_table[QUIT] = &Irssi_serv::ft_quit;
	action_table[JOIN] = &Irssi_serv::ft_join;
	action_table[PRIVMSG] = &Irssi_serv::ft_privmsg;
	action_table[WHO] = &Irssi_serv::ft_who;
	action_table[KICK] = &Irssi_serv::ft_kick;
	action_table[INVITE] = &Irssi_serv::ft_invite;
	action_table[TOPIC] = &Irssi_serv::ft_topic;
	action_table[PART] = &Irssi_serv::ft_part;
	action_table[PASS] = &Irssi_serv::ft_pass;
	action_table[IDK] = &Irssi_serv::ft_idk;

	/////
	mode_table[I]		= 	&Irssi_serv::ft_mode_i;
	mode_table[T]		= 	&Irssi_serv::ft_mode_t;
	mode_table[K]		= 	&Irssi_serv::ft_mode_k;
	mode_table[O]		= 	&Irssi_serv::ft_mode_o;
	mode_table[L]		= 	&Irssi_serv::ft_mode_l;
	mode_table[NO_MODE]	= 	&Irssi_serv::ft_mode_none;

}

Irssi_serv::~Irssi_serv()
{
}
