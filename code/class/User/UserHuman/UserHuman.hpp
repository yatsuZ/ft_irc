/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserHuman.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:37:41 by yzaoui            #+#    #+#             */
/*   Updated: 2025/02/03 13:00:06 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../User.hpp"
#include "./../../Client/Client.hpp"

class UserHuman: public User, public Client
{
public:
	UserHuman();
	UserHuman(std::string & nick, Client & client);
	~UserHuman();
};

std::ostream & operator<<( std::ostream & o, UserHuman const & userhuman);