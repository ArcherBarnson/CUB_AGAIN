/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:56:03 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/31 14:12:44 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_extension(char *file)
{
	int	i;

	i = 0;
	while (file && file[i])
		i++;
	i--;
	if (file[i] == 'b' && file[i - 1] == 'u'
		&& file[i - 2] == 'c' && file[i - 3] == '.')
		return (0);
	return (1);
}

int	check_textures(t_game *g)
{
	int	i;

	i = 0;
	while (g->raw_map[i][0] == '\n')
		i++;
	if (g->raw_map[i][0] != 'N' && g->raw_map[i][0] != 'S'
		&& g->raw_map[i][0] != 'E' && g->raw_map[i][0] != 'W'
		&& g->raw_map[i][0] != 'C' && g->raw_map[i][0] != 'F')
	{
		write(2, BAD_ID, 35);
		return (1);
	}
	while (g->raw_map[i] != NULL && i != -1 && g->raw_map[i][0] != '1')
		i = get_id(g, i);
	if (check_id_validity(g) == 0)
		return (0);
	write(2, BAD_ID, 35);
	return (1);
}

int	check_bounds(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (map[0][++j] && map[0][j] != '\n')
	{
		if (map[0][j] != '1')
			return (1);
	}
	while (map[++i] != NULL)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
			j++;
		if (map[i][0] != '1' || map[i][j - 1] != '1')
			return (1);
	}
	while (map[i - 1][++j] && map[i - 1][j] != '\n')
	{
		if (map[i - 1][j] != '1')
			return (1);
	}
	return (0);
}

int	check_tiles(char **map)
{
	int	i;
	int	j;
	int	spawn;

	i = -1;
	j = -1;
	spawn = 0;
	while (map[++i] != NULL)
	{
		while (map[i][++j] && map[i][j] != '\n')
		{
			if (!is_a_valid_tile(map[i][j]))
				return (1);
			if (is_a_valid_tile(map[i][j]) == 2 && spawn == 1)
				return (1);
			else if (is_a_valid_tile(map[i][j]) == 2 && spawn == 0)
				spawn = 1;
		}
		j = -1;
	}
	if (spawn == 0)
		return (1);
	return (0);
}

int	ft_parsing(t_game *g, char *filename)
{
	if (check_extension(filename) != 0)
	{
		write(2, BAD_EXT, 34);
		return (1);
	}
	g->raw_map = read_map(filename);
	if (g->raw_map == NULL)
		return (1);
	if (check_textures(g) != 0)
		return (2);
	g->m->map = get_map(g->raw_map);
	if (g->m->map == NULL || check_tiles(g->m->map) != 0
		|| floodfill(g->m->map) != 0)
	{
		write(2, MAP_ERR, 32);
		return (3);
	}
	write(1, "FILE OK\n", 8);
	g->t->fc[0] = get_hex_color(g->t->f);
	g->t->fc[1] = get_hex_color(g->t->c);
	return (0);
}
