/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Library.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:28:01 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/22 01:38:45 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "color.hpp"

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <unistd.h>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <typeinfo> // Pour typeid

bool	compare_str_char(const char &c, const std::string& str);
long ft_atol_limits(const std::string& str, long min, long max, bool *error);
std::string intToString(int value);
std::vector<std::string> ft_split(const std::string& , const std::string& );

std::ostream & operator<<( std::ostream & o, Action const & action);
std::ostream & operator<<( std::ostream & o, Color const & color);
ssize_t	is_sep(char c, std::string str);
