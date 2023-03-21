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

t_game	*init(void)
{
	t_game *g;

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
	g->m = malloc(sizeof(t_map));
	if (!g->m)
	{
		free(g->m);		//free all
		free(g);
		return (NULL);
	}
	g->t = malloc(sizeof(t_textures));
	if (!g->t)
		return (NULL);		//free all
	g->p = malloc(sizeof(t_player));
	if (!g->p)
		return (NULL);		//free all
	g->mlx = NULL;
	g->img = malloc(sizeof(t_data));
	if (!g->img)
		return (NULL);
	//g->win = NULL;
	return (g);
}
