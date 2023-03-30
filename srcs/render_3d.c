/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/30 03:28:57 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_slice(t_game *g, t_slice *slice)
{
	int	y;
	float	ratio = 0.0;

	y = 0;
	ratio = (slice->wall_end - slice->wall_start) / TILE_SIZE_F;
	if (ratio == 0.0)
		ratio = 0.1;
	if (ratio < 1.0 && ratio > 0.0)
		ratio = 1 / ratio;
	//printf("\n$$$$$$$$$$$$$$$$$$\nTXT_XPOS(px) = %f\nRATIO = %f\n$$$$$$$$$$$$$$$$$$\n", slice->wall_pos, ratio);
	while (y < RES_Y)
	{
		if (y < slice->wall_start)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[1]);
		else if (y > slice->wall_start && y <= slice->wall_end && slice->wall_pos != 0)
		{
			g->img->addr[y * 4 * g->img->line_length / 4 + slice->pos_x * 4] = g->t->no_t.addr[(int)((float)(y - slice->wall_start) / ratio) * g->t->no_t.line_length + ((int)slice->wall_pos * 4)];
		}
		else if (y > slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[0]);
		y++;
	}
}

/*
void	fill_image(t_game *g)				//debug funct
{
	int	i = 0;
	int	j = 0;

	while (i < RES_X)
	{
		while (j < RES_Y)
		{
			my_mlx_pixel_put(g->img, j, i, g->t->fc[0]);
			j++;
		}
		i++;
	}
	return ;
}
*/

void	render_image(t_game *g)
{
	int	i;
	int	wall_size;
	t_pos	*p;
	t_slice	slice;

	i = 0;
	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	p = insert_rays(g);
	if (p->info->dist <= 0)
		p->info->dist = 1;
	wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
	slice.pos_x = 0;
	while (i < RES_X - 1)
	{
		slice.pos_x = i;
		//printf("--------------------\nx = %i\n---------------------", slice.pos_x);
		if (!p->info->next)
			return ;
		p->info = p->info->next;
		if (p->info->dist <= 0)
			p->info->dist = 1;
		wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
		////////////////////////wip/////////////////////////////
		slice.wall_pos = ((p->info->pos_x + p->info->pos_y) % TILE_SIZE) * 100.0 / TILE_SIZE_F;
		printf("\n############wall_pos = %i\n###############\n", (int)slice.wall_pos);
		//else
		//	slice.wall_pos = (p->info->pos_y % TILE_SIZE) * 100 / TILE_SIZE;
		////////////////////////////////////////////////////////
		slice.wall_start = RES_Y / 2 - wall_size / 2;
		slice.wall_end = RES_Y / 2 + wall_size / 2;
		slice.wall_pos = slice.wall_pos * TILE_SIZE_F / 100.0;
		draw_slice(g, &slice);
		i++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}
