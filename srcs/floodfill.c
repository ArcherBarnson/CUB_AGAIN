/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:49:35 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/15 11:33:04 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != NULL)
		i++;
	return (i);
}

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

int	check_middle_limits(char **map, int *bounds_coords, int i, int j)
{
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] == ' ')
			;
		if (map[i][j] != '1')
			return (-1);
		if (map[i][bounds_coords[i] - 1] == ' ')
		{
			j = bounds_coords[i] -1;
			while (map[i][j] == ' ')
				j--;
		}
		if (map[i][j] != '1')
			return (-1);
	}
	return (i);
}

int	check_limits(char **map, int *bounds_coords)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[0][++j] != '\n')
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (1);
	}
	i = check_middle_limits(map, bounds_coords, i, j);
	if (i == -1)
		return (1);
	i--;
	j = -1;
	while (map[i][++j] != '\n')
	{
		if (map[i][j] != '1' && map[i][j] != ' ')
			return (1);
	}
	return (0);
}

int	floodfill(char **map)
{
	int	*start_coords;
	int	*bounds_coords;
	int	y_max;
	char	**pos_map;

	y_max = 0;
	start_coords = get_player_coords(map);
	if (start_coords[0] == -1)
		return (1);
	bounds_coords = get_bounds_coords(map);
	y_max = get_tab_size(map);
	pos_map = init_pos_map(map);
	if (!bounds_coords || !pos_map)
		return (1);
	if (start_coords[1] == 0 || start_coords[1] == y_max
		|| start_coords[0] <= 0
		|| start_coords[0] == bounds_coords[start_coords[1]])
		return (2);
	if (check_limits(map, bounds_coords) != 0)
		return (3);
	if (flood(map, pos_map, start_coords, bounds_coords) == 1)
		return (3);
	free(start_coords);
	free(bounds_coords);
	free_tab(pos_map);
	return (0);
}
