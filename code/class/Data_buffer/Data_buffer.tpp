/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data_buffer.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:19:53 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/26 21:46:20 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Data_buffer.hpp"

//////////////////////////////////////////////////////////// Constructeur Destructeur de la class

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
		*to_do = DISCONNECT;
}

template <typename T>
Data_buffer<T>::~Data_buffer()
{
}

//////////////////////////////////////////////////////////// Methode GET de la class

template <typename T>
std::vector<std::string>	Data_buffer<T>::get_data_in_vector_of_line(void) const
{
	// il coupe chaque ligne
	return (ft_split(this->get_data_in_string(), SEPERATOR_WITHOUT_SPACE_AND_TAB));
}


template <typename T>
std::string	Data_buffer<T>::get_data_in_string(void) const
{
	return (std::string(this->_data.data()));
}
