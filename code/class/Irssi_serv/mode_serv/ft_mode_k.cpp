/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_k.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:26:10 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/04 19:25:47 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Mode	Irssi_serv::ft_mode_k(Cmd_irssi &cmd, UserHuman * human, pollfd &current_pollfd, Channel *chan)
{
	(void)cmd;
	(void)chan;
	(void)human;
	(void)current_pollfd;
	// std::vector<std::string> mode = cmd_args[1];

	// if (cmd_args.size() < 3) //return INVALIDMODEPARAM instead... ou meme pas
	// 	return	(send_message(ERR_NEEDMOREPARAMS(this->get_name(), human->get_name(), "MODE"), current_pollfd), NO_MODE);
	// if (mode[0] == "+k")
	// {
	// 	chan->set_key(cmd_args[2]);	
	// }
	// else if (mode[0] == "-k")
	// {
	// 	chan->set_key("");	
	// }
	return (NO_MODE);
}