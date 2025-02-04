/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:24:06 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/04 19:13:43 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

Reaction_Serv	Irssi_serv::ft_user(Cmd_irssi &current_cmd, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	(void)	current_cmd;
	(void)	current_pollfd;
	(void)	index_of_current_pollfd;

	std::string	username;
	std::string	hostname;
	std::string	servername;
	std::string	realname;

	size_t last = _all_User.size() - 1; 

	std::cout << PINK << "-------- USER -----------" << NOCOLOR << std::endl;

	std::vector<std::string> l_args = current_cmd.get_arg();
	if (l_args.size() != 4)
	{
		// send_message("Error 461: USER need more args");
		return (NONE);
	}

	// TO DO : comment verifier si l'utilisateur est deja enregistré ?
	//	(Pour ne pas accepter que l'user retape la cmd apres connexion)
	// Methode 1 / verifier s'il existe un user avec exactement les meme args

	username = l_args[0];
	hostname = l_args[1]; 	// et si arg == '0' ? => recup hostname avec gethostbyname ?
	servername = l_args[2]; // et si arg == '*' ? => set auto a ircserv ?
	realname = l_args[3];

	if (realname[0] == ':')
		realname.erase(1,1);
	
	//USER etant appelé après NICK
	//les informations doivent etre donnés au dernier user ayant utilisé NICK
	
	_all_User[last].setName(username);
	_all_User[last].setHostname(hostname);
	_all_User[last].setServername(servername);
	_all_User[last].setRealname(realname);


	
	return (NONE);
}