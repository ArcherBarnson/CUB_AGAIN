/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:05:19 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/22 18:03:25 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player_data(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	if (!g || !g->m)
		return ;
	while (g->m->map[i])
	{
		while (g->m->map[i][++j])
		{
			if (g->m->map[i][j] == 'N')
			{
				g->p->x = j * TILE_SIZE;
				g->p->x += TILE_SIZE / 2;
				g->p->y = i * TILE_SIZE;
				g->p->y += TILE_SIZE / 2;
				g->p->direction = 90;
			}
		}
		j = -1;
		i++;
	}
	g->p->speed = TILE_SIZE / 2;		//tmp arbitrary value
	return ;
}
