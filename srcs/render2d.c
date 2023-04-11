/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:22:32 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/29 22:04:38 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_tile(t_game *g, int start_pos[2], int map_pos[2], int tile_size)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = 0;
	if (g->m->map[map_pos[1]][map_pos[0]] == '1')
		color = RED;
	if (g->m->map[map_pos[1]][map_pos[0]] == '0'
		|| g->m->map[map_pos[1]][map_pos[0]] == 'N')
		color = BLUE;
	while (x < tile_size -1)
	{
		while (y < tile_size -1)
		{
			my_mlx_pixel_put(g->img, start_pos[1] + y, start_pos[0] + x, color);
			y++;
		}
		x++;
		y = 0;
	}
	return ;
}

int	get_n_cols(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	return (i);
}

void	draw_scene(t_game *g)
{
	int	canvas_pos[2];
	int	map_pos[2];
	int	n_cols;

	map_pos[0] = 0;
	map_pos[1] = 0;
	canvas_pos[0] = 0;
	canvas_pos[1] = 0;
	n_cols = 0;
	while (map_pos[1] < get_tab_size(g->m->map))
	{
		n_cols = get_n_cols(g->m->map[map_pos[1]]);
		while (map_pos[0] <= n_cols)
		{
			draw_tile(g, canvas_pos, map_pos, TILE_SIZE / 5);
			map_pos[0]++;
			canvas_pos[1] += TILE_SIZE / 5;
		}
		canvas_pos[1] = 0;
		canvas_pos[0] += TILE_SIZE / 5;
		map_pos[1]++;
		map_pos[0] = 0;
	}
	my_mlx_pixel_put(g->img, (int)g->p->x / 5, (int)g->p->y / 5, GREEN);
}
