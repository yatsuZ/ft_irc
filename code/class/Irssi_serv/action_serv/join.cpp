/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:15:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/19 19:15:02 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../Irssi_serv.hpp"
/* ---> JOIN <channel>{,<channel>} [<key>{,<key>}]
			/JOIN lobbyA,lobbyB Akey,Bkey
		Permet de rejoindre et creéer un ou plusieurs channels 
*/

//TO DO: 	check si chan sur invit avant de join (ajouter mode channels)
//			message d'infos sur le serv join  (optionnel)
Reaction_Serv	Irssi_serv::ft_join(Cmd_irssi &current_cmd, UserHuman * current_user, pollfd &current_pollfd, size_t &index_of_current_pollfd)
{
	std::vector<std::string> cmd_args;
	std::vector<std::string> chans;
	std::vector<std::string> keys;

	std::cout << PINK <<  "-------- JOIN ----------- (doit ecrire ce que sa fais)" << NOCOLOR << YELLOW << "INDEX_FD : " << BLUE << index_of_current_pollfd << NOCOLOR << std::endl;
	
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
	for (size_t	i=nb_key - 1; i < chans.size(); i++)
		keys.push_back("");

	for (size_t i=0; i<chans.size(); i++)
	{
		Channel * channel =_get_channel_by_name(chans[i]);
		if (channel == NULL)
		{
			Channel new_chan(chans[i], "");
			_all_Channel.push_back(new_chan);
		
			send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
				"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] +  +CRLF, current_pollfd);
			current_user->add_channel(new_chan);
		}else
		{
			send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
				"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] + keys[i] + CRLF, current_pollfd);
			current_user->add_channel(*channel);
		}
	}

	return (NONE);
}