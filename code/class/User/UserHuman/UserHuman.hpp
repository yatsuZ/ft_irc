/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/16 17:21:01 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../User.hpp"
#include "./../../Client/Client.hpp"

class UserHuman: public User, public Client
{
private:
	int	_step_of_link;

public:
	UserHuman();
	UserHuman(std::string & nick, Client & client);
	UserHuman(Client & client);
	~UserHuman();
	void	get_msg_by_step(const std::string & server_name, pollfd &pollfd);
	void	get_welcolm(const std::string & server_name, Action from_this_action, pollfd &pollfd);
};

std::ostream & operator<<( std::ostream & o, UserHuman const & userhuman);
std::ostream & operator<<( std::ostream & o, std::vector<UserHuman> const & userhumans);
