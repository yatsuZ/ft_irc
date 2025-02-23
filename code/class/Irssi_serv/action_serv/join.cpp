/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:15:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/23 12:41:05 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"

/* ---> JOIN <channel>{,<channel>} [<key>{,<key>}]
			/JOIN lobbyA,lobbyB Akey,Bkey
		Permet de rejoindre et creéer un ou plusieurs channels 
*/

//TO DO: 	check si chan sur invit avant de join (donc ajouter les mode de channels)
//			message d'infos sur le serv join 
Reaction_Serv	Irssi_serv::ft_join(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::vector<std::string> cmd_args;
	std::vector<std::string> chans;
	std::vector<std::string> keys;

	std::cout << PINK <<  "-------- JOIN --------" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;

	size_t	nb_key = 0;
	cmd_args = current_cmd.get_arg();
	
	if (cmd_args.empty())
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), (NONE));

	chans = ft_split2(cmd_args[0], ","); //liste de noms de channels a rejoindre

	if (cmd_args.size() > 1)
	{
		nb_key = keys.size();
		keys = ft_split2(cmd_args[1], ","); //liste de cles de channels fournis
	}

	// push une string vide dans keys[] pour cas de join channel avec/sans clé 
	for (size_t i = nb_key; i < chans.size(); i++)
		keys.push_back("");

	std::cout << "SIZE KEYS = " << keys.size() << std::endl;


///////////////////////////////////////////////

	for (size_t i=0; i<chans.size(); i++)
	{
		Channel * channel =_get_channel_by_name(chans[i]);
		if (channel == NULL) //cas channel n'existe pas (on en crée un)
		{
			Channel new_chan(chans[i], "");
			new_chan.add_user(current_user);
			current_user->add_channel(&new_chan);
			_all_Channel.push_back(new_chan);
			if (keys[i].empty())
				send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
					"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] + CRLF, current_pollfd);
			else
				send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
					"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] + " " + keys[i] + CRLF, current_pollfd);
			send_message(RPL_TOPIC(this->get_name(), current_user->get_nick(), new_chan.get_name(), new_chan.get_topic()), current_pollfd);
			send_message(":" + get_name() + " 353 " + current_user->get_nick() + " = " + new_chan.get_name() + " :" + new_chan.list_user() + CRLF, current_pollfd);
			send_message(":" + get_name() + " 366 " + new_chan.get_name() + " :End of /NAMES list, chan name=" +  new_chan.get_name() + CRLF, current_pollfd);
		}else //cas channel existant
		{
			channel->add_user(current_user);
			current_user->add_channel(channel);
			send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
				"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] + " " + keys[i] + CRLF, current_pollfd);
			send_message(":" + get_name() + " 353 " +current_user->get_nick() + " = " + channel->get_name() + " :" +
				channel->list_user() + CRLF, current_pollfd);
			send_message(":" + get_name() + " 366 " + channel->get_name() + " :End of /NAMES list" + CRLF, current_pollfd);
		}
	}
	return (NONE);
}


	// for (size_t i=0; i<chans.size(); i++)
	// {
	// 	Channel * channel =_get_channel_by_name(chans[i]);
	// 	if (channel == NULL) //cas channel n'existe pas (on en crée un)
	// 	{
	// 		Channel *new_chan = new Channel(chans[i], keys[i]);
	// 		current_user->add_channel(new_chan);
	// 		_all_Channel.push_back(*new_chan);
	// 		send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
	// 			"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] +  +CRLF, current_pollfd);
	// 		// send_message(":" + get_name() + " 353 " +current_user->get_nick() + " = " + new_chan.get_name() + " :" + new_chan.list_user(), current_pollfd);
	// 		// send_message(":" + get_name() + " 366 " + new_chan.get_name() + " :End of /NAMES list", current_pollfd);

	// 	}else //cas channel existant
	// 	{
	// 		current_user->add_channel(channel);
	// 		send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
	// 			"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] + keys[i] + CRLF, current_pollfd);
	// 		send_message(":" + get_name() + " 353 " +current_user->get_nick() + " = " + channel->get_name() + " :" + channel->list_user(), current_pollfd);
	// 		send_message(":" + get_name() + " 366 " + channel->get_name() + " :End of /NAMES list", current_pollfd);
	// 	