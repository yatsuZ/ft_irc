/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data_buffer.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:19:53 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 01:01:26 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Data_buffer.hpp"


template <typename T>
Data_buffer<T>::Data_buffer(int client_fd, Action *to_do): _data(), _total_bytes_received(0)
{
	this->_data.assign(BUFFER_SIZE + 1, 0);
	ssize_t bytes_received = 0;
	while (true)
	{
		bytes_received = recv(client_fd, this->_data.data() + this->_total_bytes_received, BUFFER_SIZE, 0);
		this->_total_bytes_received += bytes_received;
				if (bytes_received != BUFFER_SIZE || is_end(_total_bytes_received, this->_data[_total_bytes_received - 1]))
			break;
		this->_data.resize(this->_data.capacity() + BUFFER_SIZE + 1);// ou reserve
	}
	
	if (bytes_received < 0)
	{
		*to_do = ERROR_RECV_DATA;
		perror("Reception failed : ");
	}

	if (!_total_bytes_received || !(is_end(_total_bytes_received, this->_data[_total_bytes_received - 1])))// verifier si il sagit dune deconxion ou une fin de lecture ??
		*to_do = DECO;
}

template <typename T>
std::vector<std::string>	&Data_buffer<T>::get_data_in_list_of_line(void) const
{
	return (ft_split_no_seperator(this->get_data_in_string(), "\n"));
}


template <typename T>
Data_buffer<T>::~Data_buffer()
{
}

template <typename T>
std::string	Data_buffer<T>::get_data_in_string(void) const
{
	std::string str = this->_data.data();
	return (str);
}

template <typename T>
std::ostream & operator<<( std::ostream & o, Data_buffer<T> const & data_buffer)
{
	o << "Data_buffer:" << std::endl;
	o << getColorCode(BLUE) << "\t_value_type: " << getColorCode(NOCOLOR) << data_buffer.get_type_string() << std::endl;
	o << getColorCode(BLUE) << "\t_total_bytes_received: " << getColorCode(NOCOLOR) << data_buffer.get_total_bytes_received() << std::endl;
	o << getColorCode(BLUE) << "\t_data:" << getColorCode(NOCOLOR) << " [";
	for (typename std::vector<T>::const_iterator it = data_buffer._data.begin();
		it != data_buffer._data.end(); ++it)
	{
		o << *it;
		if (it + 1 != data_buffer._data.end())
			o << ", ";
	}
	o << "]" << std::endl;
	return o;
}
