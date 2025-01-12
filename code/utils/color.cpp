/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:43:08 by yzaoui            #+#    #+#             */
/*   Updated: 2025/01/12 18:51:37 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/color.hpp"

const char* colorCodes[COLOR_COUNT] = {
    "\033[0m",  // NOCOLOR
    "\033[31m", // RED
    "\033[32m", // GREEN
    "\033[33m", // YELLOW
    "\033[34m", // BLUE
    "\033[35m", // MAGENTA
    "\033[36m", // CYAN
    "\033[37m", // WHITE
};

const char* getColorCode(Color color) {
	if (color >= 0 && color < COLOR_COUNT)
		return colorCodes[color];
	return "\033[0m"; // Couleur par défaut
}
