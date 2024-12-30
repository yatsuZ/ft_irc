/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Library.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 06:28:01 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/27 09:14:25 by yzaoui           ###   ########.fr       */
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
#include <stdexcept>
#include <sstream>
#include <cctype>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>		// pour EXIT_SUCCESS, EXIT_FAILURE
#include <iostream>
#include <sys/epoll.h>


long ft_atol_limits(const std::string& str, long min, long max, bool *error);