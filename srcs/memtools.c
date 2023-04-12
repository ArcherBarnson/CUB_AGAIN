/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:05:48 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/12 13:55:23 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_game(t_game *g)
{
	free(g->m->no);
	free(g->m->so);
	free(g->m->we);
	free(g->m->ea);
	free(g->m->f);
	free(g->m->c);
	free_tab(g->m->map);
	free_tab(g->raw_map);
	free(g->m);
	if (g->img->img)
		mlx_destroy_image(g->mlx, g->img->img);
	mlx_destroy_image(g->mlx, g->t->no_t.img);
	mlx_destroy_image(g->mlx, g->t->so_t.img);
	mlx_destroy_image(g->mlx, g->t->we_t.img);
	mlx_destroy_image(g->mlx, g->t->ea_t.img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->t);
	free(g->p);
	free(g->pos);
	free(g->img);
	free(g->mlx);
	free(g);
	exit(0);
}

void	free_floodfill(int *sc, int *bc, char **pos_map)
{
	free(sc);
	free(bc);
	free_tab(pos_map);
}

void	free_map_ids(t_map *m)
{
	free(m->no);
	free(m->so);
	free(m->ea);
	free(m->we);
	free(m->f);
	free(m->c);
	free_tab(m->map);
	free(m);
}

t_game	*init_failure(t_game *g)
{
	if (g != NULL)
	{
		if (g->raw_map != NULL)
			free_tab(g->raw_map);
		if (g->m != NULL)
			free_map_ids(g->m);
		if (g->t != NULL)
			free(g->t);
		if (g->p != NULL)
			free(g->p);
		if (g->img != NULL)
			free(g->img);
		if (g->mlx)
		{
			mlx_destroy_display(g->mlx);
			free(g->mlx);
		}
		free(g);
		g = NULL;
	}
	return (NULL);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	return ;
}
