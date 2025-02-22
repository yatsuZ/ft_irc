/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:46:43 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/22 18:50:04 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>



std::string list_user(std::vector<std::string> _users)
{
	std::string	list = "";
	if (_users.empty())
		return list;
	for (size_t i=0; i<_users.size(); i++)
	{
		list += _users[i];
		if (i + 1 < _users.size())
			list += " ";
	}
	return list;
}

int main(void)
{
	std::vector<std::string> vect;
	vect.push_back("Kuro");
	vect.push_back("Pachim");
	vect.push_back("sleepy");
	std::cout << "list :" + list_user(vect) << std::endl;
}
