/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:55:24 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/15 17:29:41 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	*get_player_coords(char **map)
{
	int	i;
	int	j;
	int	*start_coords;

	i = -1;
	j = -1;
	start_coords = malloc(sizeof(int) * 2);
	if (!start_coords)
		return (NULL);
	start_coords[0] = -1;
	while (map && map[++i])
	{
		while (map[i][++j] && map[i][j] != '\n')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				start_coords[0] = j;
				start_coords[1] = i;
				return (start_coords);
			}
		}
		j = -1;
	}
	return (NULL);
}

int	*get_bounds_coords(char **map)
{
	int	i;
	int	size;
	int	*bounds_coords;

	i = -1;
	size = get_tab_size(map);
	if (size <= 2)
		return (NULL);
	bounds_coords = malloc(sizeof(int) * (size + 1));
	if (!bounds_coords)
		return (NULL);
	while (map[++i])
		bounds_coords[i] = ft_strlen(map[i]) - 1;
	bounds_coords[i] = -1;
	return (bounds_coords);
}

char	**init_pos_map(char **map)
{
	int		i;
	int		j;
	char	**pos_map;

	i = -1;
	j = 0;
	while (map[j])
		j++;
	pos_map = malloc(sizeof(char *) * (j + 1));
	if (!pos_map)
		return (NULL);
	pos_map[j] = NULL;
	while (map[++i])
	{
		j = -1;
		pos_map[i] = ft_strdup(map[i]);
		while (pos_map[i][++j] && pos_map[i][j] != '\n')
			pos_map[i][j] = '0';
	}
	return (pos_map);
}
