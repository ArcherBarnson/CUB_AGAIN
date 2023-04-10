/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:05:19 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/22 19:28:04 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_player_dir(char tile)
{
	if (tile == 'N')
		return (90);
	if (tile == 'S')
		return (270);
	if (tile == 'E')
		return (0);
	if (tile == 'W')
		return (180);
	return (1);
}

void	init_player_data(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!g || !g->m)
		return ;
	while (g->m->map[++i])
	{
		while (g->m->map[i][++j])
		{
			if (g->m->map[i][j] == 'N' || g->m->map[i][j] == 'S'
				|| g->m->map[i][j] == 'W'
				|| g->m->map[i][j] == 'E')
			{
				g->p->x = j * TILE_SIZE + TILE_SIZE / 2;
				g->p->y = i * TILE_SIZE + TILE_SIZE / 2;
				g->p->direction = init_player_dir(g->m->map[i][j]);
			}
		}
		j = -1;
	}
	g->p->speed = SPEED;
	return ;
}
