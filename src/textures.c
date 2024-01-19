/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgaertne <bgaertne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:37:29 by bgaertne          #+#    #+#             */
/*   Updated: 2024/01/19 12:54:24 by bgaertne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_wall_orient(double px, double py, double wx, double wy)
{
	if (fmod(wx, 1.0) == 0.0)
	{
		// vertical
		if (px < wx)
			return (4); // west
		if (px > wx)
			return (3); // east
	}
	else if (fmod(wy, 1.0) == 0.0)
	{
		// horizontal
		if (py < wy)
			return (2); // south
		if (py > wy)
			return (1); // north
	}
}