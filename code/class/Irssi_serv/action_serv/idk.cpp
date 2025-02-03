/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idk.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:26:28 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/03 13:26:41 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_idk(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;
	std::cout << YELLOW << "-------- I DONT KNOW ?? -----------" << NOCOLOR << std::endl;

	// std::cout << current_cmd << std::endl;
	return (NONE);
}
