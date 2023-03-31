/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:54:24 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/31 14:12:43 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_n_lines(int fd)
{
	int	n;
	char	*dud;

	n = 1;
	dud = NULL;
	if (fd < 0)
		return (n);
	dud = get_next_line(fd);
	while (dud != NULL)
	{
		free(dud);
		dud = get_next_line(fd);
		n++;
	}
	free(dud);
	return (n);
}

char	**alloc_raw_map(int fd)
{
	char	**returnalloc;
	int	size;

	returnalloc = NULL;
	size = get_n_lines(fd);
	close(fd);
	if (size <= 1)
		return (returnalloc);
	returnalloc = malloc(sizeof(char *) * (size + 1));
	if (!returnalloc)
		return (NULL);
	return (returnalloc);
}

int	is_a_valid_tile(char tile)
{
	if (tile == '1' || tile == '0' || tile == ' ')
		return (1);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (2);
	return (0);
}

int	is_a_dir(char *filename)
{
	if (open(filename, O_DIRECTORY) > 0)
	{
		write(2, IS_A_DIR, 44);
		return (1);
	}
	return (0);
}

char	**read_map(char *filename)
{
	int	map_fd;
	int	i;
	char	**raw_map;

	map_fd = 0;
	i = -1;
	raw_map = NULL;
	if (is_a_dir(filename))
		return (NULL);
	map_fd = open(filename, O_RDONLY);
	if (map_fd <= 0)
		write(2, OPEN_ERROR, 71);
	else
	{
		raw_map = alloc_raw_map(map_fd);
		if (!raw_map)
			return (write(2, EMPTY_FILE, ft_strlen(EMPTY_FILE)), NULL);
		map_fd = open(filename, O_RDONLY);
		raw_map[++i] = get_next_line(map_fd);
		while (raw_map[i++] != NULL)
			raw_map[i] = get_next_line(map_fd);
		close(map_fd);
	}
	return (raw_map);
}

char	**get_map(char **raw_map)
{
	int	i;
	int	j;
	char	**returnmap;

	i = 0;
	j = 0;
	returnmap = NULL;
	while (raw_map[i] != NULL && raw_map[i][0] != '1'
		&& raw_map[i][0] != '0' && raw_map[i][0] != ' ')
		i++;
	while (raw_map[i + j])
		j++;
	returnmap = malloc(sizeof(char *) * (j + 1));
	if (!returnmap)
		return (NULL);
	j = 0;
	while (raw_map[i + j])
	{
		returnmap[j] = ft_strdup(raw_map[i + j]);
		j++;
	}
	returnmap[j] = NULL;
	free_tab(raw_map);
	return (returnmap);
}
