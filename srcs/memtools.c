/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:05:48 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/02 15:27:56 by bgrulois         ###   ########.fr       */
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

t_game	*init_failure(t_game *g)
{
	if (g != NULL)
	{
		if (g->m != NULL)
			free(g->m);
		if (g->t != NULL)
			free(g->t);
		if (g->p != NULL)
			free(g->p);
		if (g->img != NULL)
			free(g->img);
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
