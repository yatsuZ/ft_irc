/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 01:22:37 by yzaoui            #+#    #+#             */
/*   Updated: 2024/07/15 19:35:26 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <iostream>

int main()
{
	// Explicitly cast the literal to uint32_t
	uint32_t networkValue = static_cast<uint32_t>(0x4294967295); 

	// Convert network value and display result
	std::cout << "Network value (big-endian): 0x" << std::hex << networkValue << std::endl;
	uint32_t hostValue = ntohl(networkValue);
	std::cout << "Host value (little-endian): 0x" << std::hex << hostValue << std::endl;

	return 0;
}
