/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_k.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:26:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/02 19:05:53 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Mode	Irssi_serv::mode_key(std::vector<string> &cmd_args, Channel *chan, UserHuman * human, pollfd &current_pollfd)
{
	std::vector<std::string> mode = cmd_args[1];

	if (cmd_args.size() < 3) //return INVALIDMODEPARAM instead... ou meme pas
		return	(send_message(ERR_NEEDMOREPARAMS(this->get_name(), human->get_name(), "MODE"), current_pollfd), NO_MODE);
	if (mode[0] == "+k")
	{
		channel->set_key(cmd_args[2]);	
	}
	else if (mode[0] == "-k")
	{
		channel->set_key("");	
	}
	return (NO_MODE);
}