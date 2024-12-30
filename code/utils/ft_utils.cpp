/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 03:21:56 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/16 03:36:55 by yzaoui           ###   ########.fr       */
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