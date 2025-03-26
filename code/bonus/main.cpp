/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:00:46 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/26 02:28:20 by kuro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"
#include "Bot.hpp"

// void	handleSignal(bool flag)
// {
// 	if (!flag)
// 	{
		
// 	}
// }

int	main(int argc, char **argv)
{

	std::cout << "ploup" << std::endl;
	try
	{
		Bot	bot(argc, argv);

		// signal(SIGINT, handleSignal);

		bot.execution();
		bot.disconnect();
	}catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}