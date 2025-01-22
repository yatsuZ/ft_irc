/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data_buffer.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:12:33 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/21 23:49:06 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./../../header/Library.hpp"


template <typename T>
class Data_buffer
{
private:
	typedef T									_value_type;
	std::vector<_value_type>					_data;
	ssize_t										_total_bytes_received;
	void debug_is_end(ssize_t taille, char c){std::cout <<"c = " << int(c) << " | taille = " << taille << std::endl;}
	bool is_end(ssize_t taille, char c){/*debug_is_end(taille, c);*/ return (taille && (c == '\n' || c == EOF || c == '\0'));}
public:
	Data_buffer(int client_fd, Action *to_do);
	~Data_buffer();
	std::string					get_data_in_string(void) const;
	std::vector<std::string>	&get_data_in_list_of_line(void) const;
	size_t						get_total_bytes_received(void) const {return this->_total_bytes_received;}
	std::string					get_type_string(void) const {return typeid(T).name();}
};

template <typename T>
std::ostream & operator<<( std::ostream & o, Data_buffer<T> const & data_buffer);

#include "./Data_buffer.tpp"