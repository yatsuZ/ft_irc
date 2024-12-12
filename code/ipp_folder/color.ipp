/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.ipp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaoui <yzaoui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:43:08 by yzaoui            #+#    #+#             */
/*   Updated: 2024/12/12 18:48:49 by yzaoui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../header/color.hpp"

inline const char* getColorCode(Color color) {
    if (color >= 0 && color < COLOR_COUNT)
        return colorCodes[color];
    return "\033[0m"; // Couleur par défaut
}
