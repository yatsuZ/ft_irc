/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 03:21:56 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/23 00:03:09 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/Library.hpp"

long ft_atol_limits(const std::string& str, long min, long max, bool *error)
{
	*error = false;
	size_t i = 0;
	long result = 0;
	bool isNegative = false;

	if (i < str.size() && str[i] == '-') {
		isNegative = true;
		++i;
	}
	else if (i < str.size() && str[i] == '+')
		++i;

	if (str[i] == '0' && str[i + 1] != 0)// si sa commence par un 0 il ne doit rien avoir apres
		*error = true;

	while (i < str.size() && std::isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		++i;
	}

	if (isNegative)
		result = result * -1;
	if ((i < str.size() && !std::isdigit(str[i]) )|| min > result || max < result )// si c'est pas un chiffre et qu'il respecte pas les born
		*error = true;

	if ((isNegative && result > 0) || (result < 0))// cas de overflow
		*error = true;
		
	return result;
}

std::string intToString(int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

/// @brief Si le char est present dans la string alors je return true
/// @param str string
/// @param c charactere que je cherche dans str
/// @return true false
bool	compare_str_char(const char &c, const std::string& str)
{
	return (str.find(c) != std::string::npos);
}

std::string::size_type close_character(std::string::size_type start, std::string::size_type end, const std::string& str, const std::string& delimiter)
{
	std::string::size_type ret = std::string::npos;
	std::string::size_type tmp = ret;
	for (size_t i = 0; i < delimiter.size(); i++)
	{
		tmp = str.find(delimiter[i], end - start);
		if (tmp != std::string::npos && (tmp < ret || ret == std::string::npos))
			ret = tmp;
	}
	return (ret);

}

/////////////////////////////// Samira part botom


/*
*/
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

std::vector<std::string> ft_split(const std::string & str, const std::string & sep)
{
	size_t						i;
	int							idx;
	std::string					word;
	std::vector<std::string>	split;

	i = 0;
	if (str.size() == 0)
		return (split);
	while (str[i] && i < str.size())
	{
		idx = is_sep(str[i], sep);
		word.push_back(str[i]);
		if (idx != -1)
		{
			// std::cout << "word=\"" << word << "\"" << std::endl;
			while (str[i] && str[i] == sep[idx])
				i++;
			split.push_back(word);
			word.clear();
		}
		else
			i++;
	}
	if (word.size() != 0)
	{
		split.push_back(word);
		word.clear();
	}
	return (split);
}
