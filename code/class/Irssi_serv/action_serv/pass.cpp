/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:01:08 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/11 15:29:37 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv   Irssi_serv::ft_pass(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
    std::cout << YELLOW << "--------PASS -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;
    if(current_cmd.get_arg().empty())
        return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), "PASS"), current_pollfd), NONE);
    if (current_user != NULL)
        return (send_message(ERR_ALREADYREGISTRED(this->get_name(), "PASS"), current_pollfd), NONE);

    std::string pass = current_cmd.get_arg()[0];
    (void)pass;
    return (NONE);
}

/*
4.1.1 Password message


      Command: PASS
   Parameters: <password>

   The PASS command is used to set a 'connection password'.  The
   password can and must be set before any attempt to register the
   connection is made.  Currently this requires that clients send a PASS
   command before sending the NICK/USER combination and servers *must*
   send a PASS command before any SERVER command.  The password supplied
   must match the one contained in the C/N lines (for servers) or I
   lines (for clients).  It is possible to send multiple PASS commands
   before registering but only the last one sent is used for
   verification and it may not be changed once registered.  Numeric
   Replies:

           ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

   Example:

           PASS secretpasswordhere
*/