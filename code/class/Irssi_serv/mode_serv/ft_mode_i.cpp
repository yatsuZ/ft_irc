/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_i.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:18:44 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/04 19:22:56 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* ----/MODE [target] [[<+/->]i]
	target = user <= rend l'user invisible
	target = channel <= rend le channel accessible sur invite uniquement
*/
Mode	Irssi_serv::ft_mode_i(Cmd_irssi &cmd_args,  UserHuman *current_user, pollfd &current_pollfd, Channel *chan)
{
	(void)cmd_args;
	(void)current_user;
	(void)current_pollfd;
	(void)chan;
	// std::string	mode = cmd_args[1];
	// UserHuman	*target_user = this->_get_userhuman_by_nick(cmd_args[0]);
	// // Channel	 	*target_chan = this-> _get_channel_by_name(cmd_args[0]);

	// //USER
	// if (target_user != NULL)
	// {
	// 	if (target_user->get_mode() != I)
	// 		return (target_user->set_mode(I), I);
	// 	else if (target_user->get_mode() == I)
	// 		return (target_user->set_mode(NO_MODE), NO_MODE);
	// }

	//CHANNEL
	// if (target_chan != NULL)
		//on invite
	return (NO_MODE);
}