/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data_buffer.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:19:53 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/20 01:41:58 by yzaoui           ###   ########.fr       */
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

	if (!(is_end(_total_bytes_received, this->_data[_total_bytes_received - 1])))// verifier si il sagit dune deconxion ou une fin de lecture ??
		*to_do = DECO;
}

template <typename T>
Data_buffer<T>::~Data_buffer()
{
}

template <typename T>
std::string	Data_buffer<T>::get_data_in_string(void)
{
	return (std::string(this->_data.data()));
}