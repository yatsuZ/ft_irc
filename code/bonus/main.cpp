/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:00:46 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/20 20:01:23 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"
#include "Bot.hpp"

int	main(int argc, char **argv)
{
	std::cout << "ploup" << std::endl;
	try
	{
		Bot	bot(argc, argv);
	}catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}