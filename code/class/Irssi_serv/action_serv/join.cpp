/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:15:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/17 15:52:03 by smlamali         ###   ########.fr       */
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

	size_t index_user = _get_index_of_userhuman_by_nick(current_user->get_nick());
///////////////////////////////////////////////

	for (size_t i=0; i<chans.size(); i++)
	{
		Channel * channel =_get_channel_by_name(chans[i]);
		if (channel == NULL) //cas channel n'existe pas (on en crée un)
		{
			Channel new_chan(chans[i], "");
			new_chan.add_user(index_user);
			new_chan.set_operator(index_user);
			current_user->add_chan(_all_Channel.size());
			_all_Channel.push_back(new_chan);
			send_message(RPL_JOIN(current_user->get_nick(), current_user->get_hostname(), current_user->get_ip_to_string(), chans[i]), current_pollfd);
			if (!new_chan.get_topic().empty())
				send_message(RPL_TOPIC(this->get_name(), current_user->get_nick(), new_chan.get_name(), new_chan.get_topic()), current_pollfd);
			send_message(RPL_NAMEREPLY(this->get_name(), current_user->get_nick(), new_chan.get_name(), get_all_user_nick_from_chan(new_chan)), current_pollfd);
			send_message(RPL_ENDOFNAMES(this->get_name(), current_user->get_nick(), new_chan.get_name()), current_pollfd);
			channel =_get_channel_by_name(chans[i]);
		}else //cas channel existant
		{
			if (channel->get_nbr_of_user() == channel->get_limit_user())
				return (send_message(ERR_CHANNELISFULL(this->get_name(), current_user->get_nick(), channel->get_name()), current_pollfd), NONE);
//			SI le chanelle est privée on ne peut pas le rejoindre SAUF si channel->is_in_invitation(index_user) alors envoyer msg derreur car privée
			if (channel->mode_in_channel(I) && !channel->is_in_invitation(index_user))
				return (send_message(ERR_INVITEONLYCHAN(this->get_name(), current_user->get_nick(), channel->get_name()), current_pollfd), NONE);
			ssize_t index_channel = _get_index_channel_by_name(channel->get_name());
			if (keys[i] != channel->get_key())
				send_message(ERR_BADCHANNELKEY(this->get_name(), current_user->get_nick(), channel->get_name()), current_pollfd);
			_send_message_to_a_chanelle(*current_user, *channel, RPL_JOIN_K(current_user->get_nick(), current_user->get_hostname(), current_user->get_ip_to_string(), chans[i], keys[i]));
			send_message(RPL_JOIN_K(current_user->get_nick(), current_user->get_hostname(), current_user->get_ip_to_string(), chans[i], keys[i]), current_pollfd);
			if (!channel->get_topic().empty())
				send_message(RPL_TOPIC(this->get_name(), current_user->get_nick(), channel->get_name(), channel->get_topic() + CRLF), current_pollfd);
			
			channel->add_user(index_user);
			current_user->add_chan(index_channel);
			
			send_message(RPL_NAMEREPLY(this->get_name(), current_user->get_nick(), channel->get_name(), get_all_user_nick_from_chan(*channel)), current_pollfd);
			send_message(RPL_ENDOFNAMES(this->get_name(), current_user->get_nick(), channel->get_name()), current_pollfd);
			std::vector<size_t> list_user = channel->get_index_users(); 
			for (size_t i=0; i<list_user.size(); i++)
			{
				std::cout << "user["<< i << "] =" << _all_User[list_user[i]].get_nick() << std::endl;  
			}
		}
		// std::cout << GREEN + "---- CHANNEL ----" + NOCOLOR << std::endl << *channel << std::endl;
		// std::cout << BLUE + "---- USER ----" + NOCOLOR << std::endl << static_cast<User>(*current_user) << std::endl;
		// show_all_chan_from_user(*current_user);
		show_all_user_from_chanelle(*channel);

		std::cout << YELLOW << "LIST USER: " << get_all_nick_from_chan(*channel) << NOCOLOR <<  std::endl;
	}

	// afficher tout les utilsature du chanelle et tout les chanelle de lutilisateur pour debeug
	return (NONE);
}

