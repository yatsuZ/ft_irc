/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:00:46 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/27 16:33:03 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bonus.hpp"
#include "Bot.hpp"

bool ft_shutdown(bool fool)
{
	static bool flag = false;
	if (fool)
		flag = true;
	std::cout << " FLAG =" << flag << std::endl;
	return (flag);
}

void	handleSignal(int signal)
{
	(void)signal;
	ft_shutdown(true);
}

int	main(int argc, char **argv)
{

	signal(SIGINT, handleSignal);

	std::cout << "ploup" << std::endl;
	try
	{
		Bot	bot(argc, argv);

		bot.execution();
		bot.disconnect();
	}catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}