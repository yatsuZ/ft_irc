/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bonus.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuro <kuro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:01:39 by smlamali          #+#    #+#             */
/*   Updated: 2025/03/26 03:24:24 by kuro             ###   ########.fr       */
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
#include <fstream>
#include <map>
#include <csignal>
#include <vector>

#define ADRESSE "127.0.0.1"
#define CRLF "\r\n"
#define BUFFERSIZE 1024

//Regular bold text
#define BRED "\e[1;31m"
#define BPNK "\e[1;32m"
#define BCYN "\e[1;36m"
#define BGRN "\e[1;37m"

//Regular text
#define RED "\e[0;31m"
#define PNK "\e[0;32m"
#define CYN "\e[0;36m"
#define GRN "\e[0;37m"
//Reset 
#define RST "\e[0m"