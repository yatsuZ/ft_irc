/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i.cpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:18:44 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/24 19:55:12 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Mode	Irssi_serv::mode_i(std::vector<string> &cmd_args, Channel *chan, UserHuman * human, pollfd &current_pollfd)
{
	std::string	mode = cmd_args[1];
	UserHuman	*target_user = this->_get_userhuman_by_nick(cmd_args[0]);
	Channel	 	*target_chan = this-> _get_channel_by_name(cmd_args[0]);


	//USER
	if (target_user != NULL)
	{
		if (mode[0] == '+')
		{
			target_user->set_mode(+i);
			send_message(":" + current_user->get_nick() + " MODE " + target_user->get_name() + " :" + cmd_args[1] + CRLF, current_pollfd);
		}
		return (i);
	}
	//CHANNEL
	if (target_chan != NULL)
	{
		if (mode[0] == "-")
		{
			
		}
	}
}