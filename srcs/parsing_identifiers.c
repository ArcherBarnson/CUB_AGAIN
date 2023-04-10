/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:54:57 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/03 17:57:15 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*parse_id(char *id)
{
	int		i;
	int		size;
	char	*tmp;

	i = 0;
	size = 0;
	tmp = NULL;
	while (id[i] && id[i] != ' ')
		i++;
	while (id[i] && id[i] == ' ')
		i++;
	size = i;
	while (id[size] && id[size] != '\n')
		size++;
	size -= i;
	tmp = malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	size = -1;
	i--;
	while (id[i] && id[i++] != '\n')
		tmp[++size] = id[i];
	tmp[size] = '\0';
	free(id);
	return (tmp);
}

int	check_id_validity(t_game *g)
{
	if (!g->m->no || !g->m->so || !g->m->ea
		|| !g->m->we || !g->m->f || !g->m->c)
		return (1);
	g->m->no = parse_id(g->m->no);
	if (!g->m->no)
		return (1);
	g->m->so = parse_id(g->m->so);
	if (!g->m->so)
		return (1);
	g->m->ea = parse_id(g->m->ea);
	if (!g->m->ea)
		return (1);
	g->m->we = parse_id(g->m->we);
	if (!g->m->we)
		return (1);
	g->t->f[0] = get_rgb(g->m->f, 0);
	g->t->f[1] = get_rgb(g->m->f, 1);
	g->t->f[2] = get_rgb(g->m->f, 2);
	g->t->c[0] = get_rgb(g->m->c, 0);
	g->t->c[1] = get_rgb(g->m->c, 1);
	g->t->c[2] = get_rgb(g->m->c, 2);
	if (g->t->f[0] == -1 || g->t->f[1] == -1 || g->t->f[2] == -1
		|| g->t->c[0] == -1 || g->t->c[1] == -1 || g->t->c[2] == -1)
		return (1);
	return (0);
}

int	get_id(t_game *g, int i)
{
	if (!g->raw_map || !g->raw_map[i])
		return (-1);
	if (g->raw_map[i][0] == 'N' && g->raw_map[i][1] == 'O'
		&& g->raw_map[i][2] == ' ')
		g->m->no = ft_strdup(g->raw_map[i]);
	if (g->raw_map[i][0] == 'S' && g->raw_map[i][1] == 'O'
		&& g->raw_map[i][2] == ' ')
		g->m->so = ft_strdup(g->raw_map[i]);
	if (g->raw_map[i][0] == 'E' && g->raw_map[i][1] == 'A'
		&& g->raw_map[i][2] == ' ')
		g->m->ea = ft_strdup(g->raw_map[i]);
	if (g->raw_map[i][0] == 'W' && g->raw_map[i][1] == 'E'
		&& g->raw_map[i][2] == ' ')
		g->m->we = ft_strdup(g->raw_map[i]);
	if (g->raw_map[i][0] == 'F' && g->raw_map[i][1] == ' ')
		g->m->f = ft_strdup(g->raw_map[i]);
	if (g->raw_map[i][0] == 'C' && g->raw_map[i][1] == ' ')
		g->m->c = ft_strdup(g->raw_map[i]);
	i++;
	while (g->raw_map[i] && g->raw_map[i][0] == '\n' && g->raw_map[i] != NULL)
		i++;
	return (i);
}
