/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:33:44 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/14 19:09:01 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_s_map(t_map *m)
{
	m->no = NULL;
	m->so = NULL;
	m->ea = NULL;
	m->we = NULL;
	m->f = NULL;
	m->c = NULL;
	m->map = NULL;
}

int	init_substructs(t_game *g)
{
	g->m = malloc(sizeof(t_map));
	if (!g->m)
		return (0);
	init_s_map(g->m);
	g->t = malloc(sizeof(t_textures));
	if (!g->t)
		return (0);
	g->t->f[0] = -1;
	g->t->f[1] = -1;
	g->t->f[2] = -1;
	g->t->c[0] = -1;
	g->t->c[1] = -1;
	g->t->c[2] = -1;
	g->p = malloc(sizeof(t_player));
	if (!g->p)
		return (0);
	g->img = malloc(sizeof(t_data));
	if (!g->img)
		return (0);
	return (1);
}

t_game	*init(void)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		return (NULL);
	g->keycode_w = W;
	g->keycode_a = A;
	g->keycode_s = S;
	g->keycode_d = D;
	g->keycode_l = LEFT;
	g->keycode_r = RIGHT;
	g->raw_map = NULL;
	g->m = NULL;
	g->t = NULL;
	g->p = NULL;
	g->img = NULL;
	g->mlx = NULL;
	g->win = NULL;
	if (!init_substructs(g))
		return (init_failure(g));
	return (g);
}
