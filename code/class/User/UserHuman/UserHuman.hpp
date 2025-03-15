/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/15 22:43:18 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../User.hpp"
#include "./../../Client/Client.hpp"
#include "./../../Dcc/Dcc.hpp"

class UserHuman: public User, public Client
{
private:
	int	_step_of_link;
	std::vector<Dcc>			_all_request_to_send_files;

public:
	UserHuman();
	UserHuman(std::string & nick, Client & client);
	UserHuman(Client & client);
	~UserHuman();
	void	get_msg_by_step(const std::string & server_name, pollfd &pollfd);
	void	get_welcolm(const std::string & server_name, Action from_this_action, pollfd &pollfd);
	bool	add_request_send_file(Dcc new_request_send);
	void	update_index_dcc(ssize_t index_to_del);
	Dcc		pop_request_dcc(Dcc & get_request);
};

std::ostream & operator<<( std::ostream & o, UserHuman const & userhuman);
std::ostream & operator<<( std::ostream & o, std::vector<UserHuman> const & userhumans);
