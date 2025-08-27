/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chalk_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiilpal <mmiilpal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:00:00 by mmiilpal          #+#    #+#             */
/*   Updated: 2025/08/27 15:16:35 by mmiilpal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3d_bonus.h"
#include <math.h>

double	normalize_angle(double angle)
{
	while (angle > M_PI)
		angle -= 2 * M_PI;
	while (angle < -M_PI)
		angle += 2 * M_PI;
	return (angle);
}

int	is_sprite_in_bounds(int x, int y)
{
	return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

double	calculate_distance(double x1, double y1, double x2, double y2)
{
	double	dx;
	double	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}
