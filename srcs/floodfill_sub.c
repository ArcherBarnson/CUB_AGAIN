/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:24:29 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/12 16:24:43 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	flood_x(char **map, char **pos_map, int *p_pos, int *bounds_coords)
{
	p_pos[0]++;
	if (flood(map, pos_map, p_pos, bounds_coords) == 1)
		return (1);
	p_pos[0] = p_pos[0] - 2;
	if (flood(map, pos_map, p_pos, bounds_coords) == 1)
		return (1);
	p_pos[0]++;
	return (0);
}

int	flood_y(char **map, char **pos_map, int *p_pos, int *bounds_coords)
{
	p_pos[1]++;
	if (flood(map, pos_map, p_pos, bounds_coords) == 1)
		return (1);
	p_pos[1] = p_pos[1] - 2;
	if (flood(map, pos_map, p_pos, bounds_coords) == 1)
		return (1);
	p_pos[1]++;
	return (0);
}

int	flood(char **map, char **pos_map, int *p_pos, int *bounds_coords)
{
	if (pos_map[p_pos[1]][p_pos[0]] == '1'
		|| map[p_pos[1]][p_pos[0]] == '1')
		return (0);
	pos_map[p_pos[1]][p_pos[0]] = '1';
	if (p_pos[0] < 0 || bounds_coords[p_pos[1]] == -1 || p_pos[1] < 0
		|| p_pos[0] >= bounds_coords[p_pos[1]]
		|| map[p_pos[1]][p_pos[0]] == ' ')
		return (1);
	if ((p_pos[0] == 0 || p_pos[1] == 0
			|| bounds_coords[p_pos[1] + 1] == -1
			|| p_pos[0] == bounds_coords[p_pos[1]])
		&& map[p_pos[1]][p_pos[0]] == '0')
		return (1);
	if (flood_x(map, pos_map, p_pos, bounds_coords) == 1
		|| flood_y(map, pos_map, p_pos, bounds_coords) == 1)
		return (1);
	return (0);
}
