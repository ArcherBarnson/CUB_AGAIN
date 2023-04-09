/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:22:32 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/09 16:42:39 by leina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_next_frame(t_game *g)
{
	//draw_scene(g);
	// insert_rays(g);
	render_image(g);
	mlx_destroy_image(g->mlx, g->img->img);
	g->img->img = NULL;
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_tile(t_game *g, int start_pos[2], int map_pos[2], int tile_size)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = 0;
	//printf("map_pos[0] = %i\n", map_pos[0]);
	//printf("map_pos[1] = %i\n", map_pos[1]);
	//printf("can_pos[0] = %i\n", start_pos[0]);
	//printf("can_pos[1] = %i\n", start_pos[1]);
	//printf("tile = %c\n", g->m->map[map_pos[1]][map_pos[0]]);
	if (g->m->map[map_pos[1]][map_pos[0]] == '1')
		color = RED;
	if (g->m->map[map_pos[1]][map_pos[0]] == '0' || g->m->map[map_pos[1]][map_pos[0]] == 'N')
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
/*
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
	g->img->img = mlx_new_image(g->mlx, 2000, 1500);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	while (map_pos[1] < get_tab_size(g->m->map))
	{
		n_cols = get_n_cols(g->m->map[map_pos[1]]);
		while (map_pos[0] <= n_cols)
		{
			draw_tile(g, canvas_pos, map_pos, TILE_SIZE);
			map_pos[0]++;
			canvas_pos[1] += TILE_SIZE;
		}
		canvas_pos[1] = 0;
		canvas_pos[0] += TILE_SIZE;
		map_pos[1]++;
		map_pos[0] = 0;
	}
	my_mlx_pixel_put(g->img, (int)g->p->x, (int)g->p->y, GREEN);
	insert_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 50, 50);
}*/
