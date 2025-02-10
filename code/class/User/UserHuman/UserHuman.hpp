/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/10 23:21:11 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../User.hpp"
#include "./../../Client/Client.hpp"

class UserHuman: public User, public Client
{
public:
	UserHuman();
	UserHuman(std::string & nick, Client & client);
	UserHuman( Client & client);
	~UserHuman();

private:
};

std::ostream & operator<<( std::ostream & o, UserHuman const & userhuman);
std::ostream & operator<<( std::ostream & o, std::vector<UserHuman> const & userhumans);
