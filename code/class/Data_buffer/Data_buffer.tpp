/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data_buffer.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:19:53 by yzaoui            #+#    #+#             */
/*   Updated: 2025/03/27 15:58:44 by smlamali         ###   ########.fr       */
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

		if (bytes_received <= 0)
			break;
		if (is_end(_total_bytes_received, this->_data[_total_bytes_received - 1]))
			break;
		
		this->_data.resize(this->_data.capacity() + BUFFER_SIZE + 1);// ou reserve
	}
	
	if (bytes_received < 0)
	{
		*to_do = ERROR_RECV_DATA;
		perror("Reception failed : ");
		return ;
	}
	
	if (_total_bytes_received == 0 || !(is_end(_total_bytes_received, this->_data[_total_bytes_received - 1])))
	{
		*to_do = DISCONNECT;
		return ;
	}
	verif_no_char_strange(to_do);
}


template <typename T>
Data_buffer<T>::~Data_buffer()
{
}

//////////////////////////////////////////////////////////// Methode GET de la class

template <typename T>
std::vector<std::string>	Data_buffer<T>::get_data_in_vector_of_line(void) const
{
	return (ft_split(this->get_data_in_string(), CRLF));
}


template <typename T>
std::string	Data_buffer<T>::get_data_in_string(void) const
{
	return (std::string(this->_data.data()));
}

/*
template <typename T>
bool Data_buffer<T>::is_end(ssize_t taille, char *c)
{
	if (taille == 0 || *c == 0 || *c == EOF)
		return (true);
	char c1 = *c;
	char c2 = *c + 1;
	if (c1 == '\r' && (c2 == '\n' || c2 == '\0' || c2 == EOF))
		return (true);
	return (false);
}
*/

template <typename T>
bool Data_buffer<T>::is_end(ssize_t taille, char c)
{
	if (taille == 0)
		return (false);
	if (c == '\n' || c == '\0')
		return (true);
	return (false);
}

template <typename T>
void Data_buffer<T>::verif_no_char_strange(Action *to_do)
{
	for (ssize_t i = 0; i < _total_bytes_received; i++)
	{
		if (_data[i] < ' ' && _data[i] != '\r' && _data[i] != '\n' && _data[i] != '\t' && _data[i] != '\0' && _data[i] != '\x01')
		{
			*to_do = ERROR_RECV_DATA;
			return ;
		}
	}
}
