/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:15:59 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/18 19:24:23 by smlamali         ###   ########.fr       */
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
	
	cmd_args = current_cmd.get_arg();

	if (cmd_args.empty())
		return (send_message(ERR_NEEDMOREPARAMS(this->get_name(), current_user->get_nick(), current_cmd.get_cmd()), current_pollfd), (NONE));

	chans = ft_split2(cmd_args[0], ","); //liste des noms de channels a rejoindre
	if (cmd_args.size() > 1)
		keys = ft_split2(cmd_args[1], ","); //liste des cles de channels


	for (size_t i=0; i<chans.size(); i++)
	{
		if (_get_channel_by_name(chans[i]) == NULL)
		{
			Channel new_chan(chans[0], "");
			_all_Channel.push_back(new_chan);
		
			send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
				"@" + current_user->get_ip_to_string() + " JOIN :" + chans[i] + CRLF, current_pollfd);
			// current_user.add_channel(new_chan);
		}
	}
	// //boucler sur taille chan pour cas multiple
	// name.push_back(cmd_args[0]);
	// if (_get_channel_by_name(name[0]) == NULL)
	// {
	// 	Channel	new_chan(name[0], "");
	// 	_all_Channel.push_back(new_chan);
	// }
	
	// return (send_message(":" + current_user->get_nick() + "!~" + current_user->get_hostname() + 
		// "@" + current_user->get_ip_to_string() + " JOIN :" + name[0] + CRLF, current_pollfd), (NONE));	
	return (send_message(ERR_UNKNOWNCOMMAND(this->get_name(), current_cmd.get_cmd()), current_pollfd), (NONE));
}