/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smlamali <smlamali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:39 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/19 20:18:47 by smlamali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <exception>
#include <cstdlib>
#include <arpa/inet.h>

#define ADRESSE "127.0.0.1"