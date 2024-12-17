/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Library.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:28:01 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/17 07:29:02 by yzaoui           ###   ########.fr       */
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

long ft_atol_limits(const std::string& str, long min, long max, bool *error);