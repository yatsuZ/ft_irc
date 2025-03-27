/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 03:01:08 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/27 15:59:12 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv   Irssi_serv::ft_pass(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
    std::cout << GREEN << "--------PASS -----------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;
    if(current_cmd.get_arg().empty())
    {
        send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), "PASS"), current_pollfd);
        return (this->ft_disconnect(current_cmd, current_user, current_pollfd, index_of_current_pollfd));
    }
    
    if (current_user->_get_is_connect())
        return (send_message(ERR_ALREADYREGISTRED(this->get_name(), "PASS"), current_pollfd), PASS_SERV);
    
    std::string pass = current_cmd.get_arg()[0];

    if (pass != this->get_mdp())
    {
        std::cout << "------ HERE -----------" << std::endl;
        send_message(ERR_PASSWDMISMATCH(this->get_name(), current_user->get_nick()), current_pollfd);
        send_message(":" + this->get_name() + " ERROR :Closing Link: localhost (Bad Password)", current_pollfd);
        return (this->ft_disconnect(current_cmd, current_user, current_pollfd, index_of_current_pollfd));
    }
    current_user->set_is_connect();
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