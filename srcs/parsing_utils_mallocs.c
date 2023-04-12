/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_mallocs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:25:11 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/12 16:25:21 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**alloc_raw_map(int fd)
{
	char	**returnalloc;
	int		size;

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

char	**read_map(char *filename)
{
	int		map_fd;
	int		i;
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
	int		i;
	int		j;
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
	return (returnmap);
}
