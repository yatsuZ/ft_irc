/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:52:18 by smlamali          #+#    #+#             */
/*   Updated: 2025/02/18 18:22:53 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <unistd.h>

//renvoie l'index du separateur dans &sep, - 1 si il trouve pas
ssize_t	is_sep(char c, std::string sep) 
{
	for(size_t i = 0; i< sep.size(); i++)
	{
		if (sep[i] == c)
			return i;
	}
	return -1;
}

std::vector<std::string> ft_split2(const std::string & str, const std::string & sep)
{
	size_t						i;
	std::string					word;
	std::vector<std::string>	split;

	if (str.empty())
		return split;

	i=0;
	while (i < str.size())
	{
		if (is_sep(str[i], sep))
		{
			std::cout << "word=" << word << std::endl;
			split.push_back(word);
			word.clear();
		}
		else
			word.push_back(str[i]);
		i++;
	}
	if (word.size() != 0)
	{
		split.push_back(word);
		word.clear();
	}
	return (split);
}

int	main(void)
{
	std::string	str = "lobbyA,lobB,LobbyC";
	std::vector<std::string>	newstr = ft_split2(str, ",");

	std::cout << "---MAIN---" << std::endl;
	for (size_t i=0; i<newstr.size(); i++)
		std::cout << "[" << newstr[i] << "]" << std::endl;
	std::cout << "---END---" << std::endl;
}