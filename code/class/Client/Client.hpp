/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:24:47 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/13 16:03:18 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./../../header/Ft_irc.hpp"

class Client
{
public:
	Client();
	Client(Client const & src);
	Client(ssize_t index_pollfd, sockaddr_in client_addr, socklen_t client_len);
	~Client();

	ssize_t			get_index_pollfd(void) const {return this->_index_pollfd;}
	void			set_index_pollfd(ssize_t new_index_pollfd) {this->_index_pollfd = new_index_pollfd;}
	sockaddr_in		get_client_addr(void) const {return this->_client_addr;}
	socklen_t		get_client_len(void) const {return this->_client_len;}
	bool			get_is_connect(void) const {return this->_is_connect;}
	std::string		get_ip_to_string(void) const;
	uint16_t		get_port(void) const;
	std::string		get_port_to_string(void) const;


protected:
	ssize_t			_index_pollfd;
	sockaddr_in		_client_addr;
	socklen_t		_client_len;
	bool			_is_connect;
};

std::ostream & operator<<( std::ostream & o, Client const & client);