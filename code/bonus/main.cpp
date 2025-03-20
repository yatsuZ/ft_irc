/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:00:46 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/20 15:38:44 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.hpp"
#include "Bot.hpp"

int	main(void)
{
	std::cout << "ploup" << std::endl;
	try
	{
		Bot	bot;
		bot.init();
	}catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}